//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbtk_audio_api.ppp
//PPL Source File Name : \\mbtk\\wav\\src\\mbtk_audio_api.c
typedef unsigned char u8 ;
typedef unsigned short u16 ;
typedef unsigned char uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int u32 ;
typedef unsigned int uint ;
typedef unsigned int uint32 ;
typedef unsigned long long u64 ;
typedef unsigned long long uint64 ;
typedef unsigned int uint_t ;
typedef unsigned char uint8_t ;
typedef unsigned short uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned long long uint64_t ;
typedef unsigned int uint_t ;
typedef unsigned char uint_8 ;
typedef unsigned short uint_16 ;
typedef unsigned int uint_32 ;
typedef unsigned long long uint_64 ;
typedef signed char int8 ;
typedef signed short int16 ;
typedef signed int int32 ;
typedef signed int int_32 ;
typedef signed long long int64 ;
typedef signed char int8_t ;
typedef signed short int16_t ;
typedef signed int int32_t ;
typedef signed long long int64_t ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned int UINT ;
typedef unsigned int UINT32 ;
typedef unsigned long long UINT64 ;
typedef int INT ;
typedef char INT8 ;
typedef short INT16 ;
typedef int INT32 ;
typedef long long INT64 ;
typedef unsigned char U8 ;
typedef unsigned short U16 ;
typedef unsigned int U32 ;
typedef int S32 ;
typedef unsigned long long U64 ;
typedef char S8 ;
typedef short S16 ;
typedef long long S64 ;
typedef char s8 ;
typedef short s16 ;
typedef int s32 ;
typedef unsigned int size_t ;
typedef char ascii ;
typedef unsigned char byte ;
typedef unsigned short word ;
typedef unsigned long dword ;
typedef unsigned char BYTE ;
typedef char CHAR ;
typedef unsigned short WCHAR ;
typedef unsigned short WORD ;
typedef signed int WORD32 ;
typedef unsigned int UWORD32 ;
typedef unsigned short RESID ;
typedef float float32 ;
typedef float FLOAT ;
typedef double DOUBLE ;
typedef UINT8* PUINT8 ;
typedef INT32* PINT32 ;
typedef UINT16* PUINT16 ;
typedef INT16* PINT16 ;
typedef CHAR * PCHAR ;
typedef void* PVOID ;
typedef char * PS8 ;
typedef unsigned char * PU8 ;
typedef short * PS16 ;
typedef unsigned short * PU16 ;
typedef int * PS32 ;
typedef unsigned int * PU32 ;
typedef unsigned short pBOOL ;
typedef volatile unsigned char REG8 ;
typedef volatile unsigned short REG16 ;
typedef volatile unsigned int REG32 ;
typedef unsigned char kal_uint8 ;
typedef signed char kal_int8 ;
typedef char kal_char ;
typedef unsigned short kal_wchar ;
typedef unsigned short int kal_uint16 ;
typedef signed short int kal_int16 ;
typedef unsigned int kal_uint32 ;
typedef signed int kal_int32 ;
typedef unsigned int HRES ;
typedef unsigned int HAO ;
typedef unsigned char u8_t ;
typedef unsigned short u16_t ;
typedef u32 mbtk_mutex ;
typedef u32 mbtk_sema ;
typedef void ( * MBTK_AUDIO_PA_HOOK ) ( int enable ) ;
typedef void ( * MBTK_AUDIO_PLAYER_CALLBACK ) ( void *param ) ;
typedef void ( *MBTK_AUDIO_RECORD_CALLBACK ) ( MBTK_MCI_EVNET event , MBTK_MCI_INFO info_type , int value ) ;
typedef void ( *mbtk_mp3_play_cb ) ( int ) ;
typedef int ( *audio_process_cb ) ( char *in_buf , int in_lens , char *out_buf , int *out_lens , int samperate , int channel , int bits ) ;
typedef void ( *mbtk_amr_play_cb ) ( int ) ;
typedef UINT8 BOOL ;
typedef void ( *MP3_EVENT_CB ) ( int ) ;
typedef void ( *MBTK_AUDIO_CONTINUE_RECORD_CALLBACK ) ( const char* , int ) ;
typedef void ( *mbtk_oem_RecordCB ) ( const char* data , int length ) ;
typedef void ( *mbtk_oem_PlayCB ) ( int rest_data ) ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef char CHAR ;
typedef signed short INT16 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_INT_IFC ,	 
 DIAG_EXT_IFC	 
 } DIAG_IF_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_DEV_USB ,	 
 DIAG_DEV_SD ,	 
 DIAG_DEV_FS ,	 
 DIAG_DEV_UART ,	 
 DIAG_DEV_SPI ,	 
 DIAG_DEV_NONE	 
 } DIAG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 SULOG_DEV_USB ,	 
 SULOG_DEV_SD	 
 } SULOG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 EEH_DUMP_DEV_USB_SD ,	 
 EEH_DUMP_DEV_SPI	 
 } EEH_DUMP_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_START_PS_OFF ,	 
 DIAG_START_PS_ON	 
 } DIAG_START_PS_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_UART_SPEED_921600 ,	 
 DIAG_UART_SPEED_1842000 ,	 
 DIAG_UART_SPEED_3000000 ,	 
 DIAG_UART_DISABLE ,	 
 } DIAG_UART_SPEED_TYPE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 DIAG_IF_TYPE useIntIf ; /* use internal interface or external interface */	 
 DIAG_UART_SPEED_TYPE useHighSpeedUART ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL GLFeatureFlag ;	 
 DIAG_START_PS_TYPE diagStartPS ;	 
 DIAG_DEV_TYPE diagDevType ;	 
 SULOG_DEV_TYPE sulogDevType ;	 
 EEH_DUMP_DEV_TYPE eehDumpDevType ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL usbUserMode ;	 
 BOOL sdlAutoDelete ;	 
 } diagCfgDataS;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT32 dbID ;	 
 UINT32 filterBitLength ;	 
 UINT32 reserved [ 6 ] ;	 
 } DIAG_Nvm_Filter_File_Header_t;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 YMODEM_DISABLE = 0x0 ,	 
 YMODEM_ENABLE = 0x1	 
 } Ymodem_Dump_config;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Ymodem_Dump_config config ;	 
 } Ymodem_Dump_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 /* MIFI driver*/	 
 USB_GENERIC_MIFI_DRIVER = 0x0 ,	 
 USB_MARVELL_MIFI_DRIVER = 0x1 ,	 
 USB_ASR_MIFI_DRIVER = 0x2 ,	 
 USB_GENERIC_MOD_DRIVER = 0x10 ,	 
 USB_GENERIC_MOD_ECM_DRIVER = 0x12 ,	 
 USB_DIAG_UAC_DRIVER = 0x14 ,	 
	 
 /* MBIM driver*/	 
 USB_MBIM_ONLY_DRIVER = 0x40 ,	 
 USB_MBIM_GENERIC_DRIVER = 0x41 ,	 
 USB_MBIM_MAX_DRIVER = 0x4F ,	 
	 
 /* Other driver*/	 
 USB_CDROM_ONLY_DRIVER = 0x91 ,	 
 USB_CDROM_DIAG_DRIVER = 0x92 ,	 
 USB_DIAG_ONLY_DRIVER = 0x93 ,	 
 USB_MODEM_ONLY_DRIVER = 0x94 ,	 
 USB_MODEM_DIAG_DRIVER = 0x95 ,	 
	 
 USB_MAX_DRIVER = 0xFF	 
 } Usb_driver_typeE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 MASS_STORAGE_DISABLE = 0x0 ,	 
 MASS_STORAGE_ENABLE = 0x1	 
 } MassStorage_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_AUTO_INSTALL_DISABLE = 0x0 ,	 
 USB_AUTO_INSTALL_ENABLE = 0x1	 
 } Usb_auto_install_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_OS_DETECT_DISABLE = 0x0 ,	 
 USB_OS_DETECT_ENABLE = 0x1	 
 } Usb_OS_detect_type;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Usb_driver_typeE usb_driver ;	 
 MassStorage_ConfigE mass_storage ;	 
 Usb_auto_install_type auto_install ;	 
 Usb_OS_detect_type os_detect ;	 
 } Usb_DriverS;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 HEAD_PHONE_INIT = 0 ,	 
 HEAD_PHONE_OUT , // 1	 
 HEAD_TYPE_UNKNOWN , // 2	 
 HEAD_PHONE_TYPE3 , // 3	 
 HEAD_PHONE_TYPE4 , // 4	 
 HEAD_PHONE_TYPE_C_REVERSE , // 5	 
 HEAD_PHONE_TYPE_C , // 6	 
	 
 HEAD_PHONE_ERROR = 0xFFFF	 
 } HEADPHONE_STATE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 HOOK_KEY_EVENT_NULL = 0 ,	 
 VOL_UP_PRESS , // 1	 
 VOL_DOWN_PRESS , // 2	 
 HOOK_KEY_PRESS , // 3	 
 VOL_UP_RELEASE , // 4	 
 VOL_DOWN_RELEASE , // 5	 
 HOOK_KEY_RELEASE , // 6	 
	 
 HEADPHONE_EVENT_ERROR = 0xFFFF	 
 } HEADPHONE_EVENT;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_ERR_NO = 0 , // No error	 
 AUDIOHAL_ERR_RESOURCE_RESET ,	 
 AUDIOHAL_ERR_RESOURCE_BUSY ,	 
 AUDIOHAL_ERR_RESOURCE_TIMEOUT ,	 
 AUDIOHAL_ERR_RESOURCE_NOT_ENABLED ,	 
 AUDIOHAL_ERR_BAD_PARAMETER ,	 
	 
 AUDIOHAL_ERR_UART_RX_OVERFLOW ,	 
 AUDIOHAL_ERR_UART_TX_OVERFLOW ,	 
 AUDIOHAL_ERR_UART_PARITY ,	 
 AUDIOHAL_ERR_UART_FRAMING ,	 
 AUDIOHAL_ERR_UART_BREAK_INT ,	 
	 
 AUDIOHAL_ERR_TIM_RTC_NOT_VALID ,	 
 AUDIOHAL_ERR_TIM_RTC_ALARM_NOT_ENABLED ,	 
 AUDIOHAL_ERR_TIM_RTC_ALARM_NOT_DISABLED ,	 
	 
 AUDIOHAL_ERR_COMMUNICATION_FAILED ,	 
	 
 /* Must be at the end */	 
 AUDIOHAL_ERR_QTY ,	 
	 
	 
 AUDIOHAL_ERR_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } AUDIOHAL_ERR_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_ITF_RECEIVER = 0 ,	 
 AUDIOHAL_ITF_EARPIECE ,	 
 AUDIOHAL_ITF_HEADPHONE = AUDIOHAL_ITF_EARPIECE ,	 
 AUDIOHAL_ITF_LOUDSPEAKER ,	 
 AUDIOHAL_ITF_LOUDSPEAKER_AND_HEADPHONE ,	 
 // AUDIOHAL_ITF_LOUDSPEAKER_AND_HEADPHONE = AUDIOHAL_ITF_LOUDSPEAKER_AND_EARPIECE ,	 
 AUDIOHAL_ITF_BLUETOOTH ,	 
 AUDIOHAL_ITF_FM ,	 
 AUDIOHAL_ITF_FM2SPK ,	 
 AUDIOHAL_ITF_TV ,	 
 AUDIOHAL_ITF_BLUETOOTH_WB ,	 
 AUDIOHAL_ITF_HS_LEFT ,	 
 AUDIOHAL_ITF_HS_RIGHT ,	 
 AUDIOHAL_ITF_VAD ,	 
 AUDIOHAL_ITF_FM2RCV ,	 
	 
 AUDIOHAL_ITF_QTY ,	 
 AUDIOHAL_ITF_NONE = 255 ,	 
 } AUDIOHAL_ITF_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_SPK_RECEIVER = 0 ,	 
 AUDIOHAL_SPK_EARPIECE ,	 
 AUDIOHAL_SPK_LOUDSPEAKER ,	 
 AUDIOHAL_SPK_LOUDSPEAKER_EARPIECE , // Output on both hands-free loud speaker and earpiece	 
	 
 AUDIOHAL_SPK_QTY ,	 
 AUDIOHAL_SPK_DISABLE = 255 ,	 
 } AUDIOHAL_SPK_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_SPEAKER_STEREO = 0 ,	 
 AUDIOHAL_SPEAKER_MONO_RIGHT ,	 
 AUDIOHAL_SPEAKER_MONO_LEFT ,	 
 AUDIOHAL_SPEAKER_STEREO_NA , // Output is mono only	 
	 
 AUDIOHAL_SPEAKER_QTY ,	 
 AUDIOHAL_SPEAKER_DISABLE = 255 ,	 
 } AUDIOHAL_SPEAKER_TYPE_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_MIC_RECEIVER = 0 ,	 
 AUDIOHAL_MIC_EARPIECE ,	 
 AUDIOHAL_MIC_LOUDSPEAKER ,	 
	 
 AUDIOHAL_MIC_QTY ,	 
 AUDIOHAL_MIC_DISABLE = 255 ,	 
 } AUDIOHAL_MIC_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_SPK_MUTE = 0 ,	 
 AUDIOHAL_SPK_VOL_1 ,	 
 AUDIOHAL_SPK_VOL_2 ,	 
 AUDIOHAL_SPK_VOL_3 ,	 
 AUDIOHAL_SPK_VOL_4 ,	 
 AUDIOHAL_SPK_VOL_5 ,	 
 AUDIOHAL_SPK_VOL_6 ,	 
 AUDIOHAL_SPK_VOL_7 ,	 
 AUDIOHAL_SPK_VOL_8 ,	 
 AUDIOHAL_SPK_VOL_9 ,	 
 AUDIOHAL_SPK_VOL_10 ,	 
 AUDIOHAL_SPK_VOL_11 , // 11	 
	 
 AUDIOHAL_SPK_VOL_QTY // 12	 
 } AUDIOHAL_SPK_LEVEL_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_MIC_MUTE = 0 ,	 
 AUDIOHAL_MIC_ENABLE ,	 
	 
 AUDIOHAL_MIC_VOL_QTY ,	 
 } AUDIOHAL_MIC_LEVEL_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_SIDE_MUTE = 0 ,	 
 AUDIOHAL_SIDE_VOL_1 ,	 
 AUDIOHAL_SIDE_VOL_2 ,	 
 AUDIOHAL_SIDE_VOL_3 ,	 
 AUDIOHAL_SIDE_VOL_4 ,	 
 AUDIOHAL_SIDE_VOL_5 ,	 
 AUDIOHAL_SIDE_VOL_6 ,	 
 AUDIOHAL_SIDE_VOL_7 ,	 
 AUDIOHAL_SIDE_VOL_TEST ,	 
 AUDIOHAL_SIDE_VOL_QTY ,	 
 } AUDIOHAL_SIDE_LEVEL_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_FREQ_8000HZ = 8000 ,	 
 AUDIOHAL_FREQ_11025HZ = 11025 ,	 
 AUDIOHAL_FREQ_12000HZ = 12000 ,	 
 AUDIOHAL_FREQ_16000HZ = 16000 ,	 
 AUDIOHAL_FREQ_22050HZ = 22050 ,	 
 AUDIOHAL_FREQ_24000HZ = 24000 ,	 
 AUDIOHAL_FREQ_32000HZ = 32000 ,	 
 AUDIOHAL_FREQ_44100HZ = 44100 ,	 
 AUDIOHAL_FREQ_48000HZ = 48000 ,	 
 AUDIOHAL_FREQ_64000HZ = 64000 ,	 
 AUDIOHAL_FREQ_88200HZ = 88200 ,	 
 AUDIOHAL_FREQ_96000HZ = 96000 ,	 
 } AUDIOHAL_FREQ_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_MONO = 1 ,	 
 AUDIOHAL_STEREO = 2 ,	 
 } AUDIOHAL_CH_NB_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_DTMF_0 = 0 ,	 
 AUDIOHAL_DTMF_1 ,	 
 AUDIOHAL_DTMF_2 ,	 
 AUDIOHAL_DTMF_3 ,	 
 AUDIOHAL_DTMF_4 ,	 
 AUDIOHAL_DTMF_5 ,	 
 AUDIOHAL_DTMF_6 ,	 
 AUDIOHAL_DTMF_7 ,	 
 AUDIOHAL_DTMF_8 ,	 
 AUDIOHAL_DTMF_9 ,	 
 AUDIOHAL_DTMF_A ,	 
 AUDIOHAL_DTMF_B ,	 
 AUDIOHAL_DTMF_C ,	 
 AUDIOHAL_DTMF_D ,	 
 AUDIOHAL_DTMF_S , // * key	 
 AUDIOHAL_DTMF_P , // # key	 
 AUDIOHAL_COMFORT_425 ,	 
 AUDIOHAL_COMFORT_950 ,	 
 AUDIOHAL_COMFORT_1400 ,	 
 AUDIOHAL_COMFORT_1800 ,	 
 } AUDIOHAL_TONE_TYPE_T;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 AUDIOHAL_TONE_0DB = 0 ,	 
 AUDIOHAL_TONE_M3DB , // -3 dB	 
 AUDIOHAL_TONE_M9DB , // -9 dB	 
 AUDIOHAL_TONE_M15DB , // -15 dB	 
 AUDIOHAL_TONE_QTY	 
 } AUDIOHAL_TONE_ATTENUATION_T;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 AUDIOHAL_HEADPHONE_PLUG_OUT = 0 ,	 
 AUDIOHAL_HEADPHONE_PLUG_IN = 1	 
 } AUDIOHAL_HEADPHONE_PLUG_T;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 AUDIOHAL_HEADPHONE_TYPE_NULL = 0 ,	 
 AUDIOHAL_HEADPHONE_TYPE_UNKNOWN = 1 ,	 
	 
 AUDIOHAL_HEADPHONE_TYPE_3 = 3 , // HEAD_PHONE_TYPE3	 
 AUDIOHAL_HEADPHONE_TYPE_4 = 4 // HEAD_PHONE_TYPE4	 
 } AUDIOHAL_HEADPHONE_TYPE_T;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 AUDIOHAL_HEADPHONE_EVENT_NULL = 0 ,	 
 AUDIOHAL_HEADPHONE_EVENT_VOLUME_UP = 1 ,	 
 AUDIOHAL_HEADPHONE_EVENT_VOLUME_DOWN= 2 ,	 
 AUDIOHAL_HEADPHONE_EVENT_HOOK_KEY = 3 ,	 
	 
 AUDIOHAL_HEADPHONE_EVENT_TYPE_C_REVERSE = 7	 
	 
 } AUDIOHAL_HEADPHONE_EVENT_T;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 AUDIOHAL_PORT_VOICE = 0 ,	 
 AUDIOHAL_PORT_SSPA = AUDIOHAL_PORT_VOICE ,	 
 AUDIOHAL_PORT_HW_SSP0 = 1 ,	 
 AUDIOHAL_PORT_SSP1 = AUDIOHAL_PORT_HW_SSP0 ,	 
 AUDIOHAL_PORT_HW_SSP1 = 2 ,	 
 AUDIOHAL_PORT_SSP2 = AUDIOHAL_PORT_HW_SSP1 ,	 
 AUDIOHAL_PORT_HW_SSP2 = 3 ,	 
 AUDIOHAL_PORT_SSP3 = AUDIOHAL_PORT_HW_SSP2 ,	 
	 
 AUDIOHAL_PORT_QTY	 
 } AUDIOHAL_DEVICE_PORT_T;

typedef void ( *AUDIOHAL_HANDLER_T ) ( void ) ;
typedef void ( *AUDIOHAL_HeadsetReport_T ) ( UINT32 plug , UINT32 type , UINT32 event ) ;
typedef void ( *AUDIOHAL_SpeakerPA_T ) ( UINT32 on ) ;
typedef void ( *AUDIOHAL_Codec_T ) ( UINT32 on ) ;
typedef void ( *AUDIOHAL_BT_CALLBACK_T ) ( UINT32 on ) ;
typedef void ( *AUDIOHAL_KWS_CB_T ) ( unsigned int key ) ;
typedef int ( *AUDIO_EXTRA_CB ) ( short* dataPtr , UINT16 dataSize ) ;
//ICAT EXPORTED STRUCT 
 typedef struct {	 
 UINT32 * startAddress ;	 
 UINT16 length ;	 
	 
 AUDIOHAL_FREQ_T sampleRate ;	 
 AUDIOHAL_CH_NB_T channelNb ;	 
 // BOOL voiceQuality ;	 
 // BOOL playSyncWithRecord ;	 
 INT voiceQuality ;	 
 INT playSyncWithRecord ;	 
	 
 AUDIOHAL_HANDLER_T halfHandler ;	 
 AUDIOHAL_HANDLER_T endHandler ;	 
 } AUDIOHAL_STREAM_T;

typedef UINT32 Attribs_Mmu ;
typedef void ( * mmuNotifyEventFunc ) ( MMU_ERROR_STATUS mmuErrorHandle ) ;
typedef union {
 rw_region_item compress_rw_region_list [ 16 ] ;

 UINT8 filer [ 512 ] ;
 } LOADTABLE_AREA_RW_CPZ_INFO ;
typedef unsigned char BYTE ;
typedef unsigned short int WORD ;
typedef WORD * WORD_PTR ;
typedef DWORD * DWORD_PTR ;
typedef BYTE BYTE_BITMASK ;
typedef VOID_PTR * VOID_PTR_PTR ;
typedef WORD FLASH_DATA_WIDTH ;
typedef char FDI_TCHAR ;
typedef OSASemaRef SEM_ID ;
typedef int SEM_STATUS ;
typedef SEM_MTX * SEM_MTX_ID ;
typedef unsigned short FILE_ID ;
typedef int ( *spi_nor_read_fun ) ( unsigned int addr , unsigned int buf_addr , unsigned int size ) ;
typedef int ( *spi_nor_write_fun ) ( unsigned int addr , unsigned int buf_addr , unsigned int size ) ;
typedef int ( *spi_nor_earse_fun ) ( unsigned int addr , unsigned int size ) ;
DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , AUDIO , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbtk_audioplayer.ppp
//PPL Source File Name : \\mbtk\\wav\\src\\mbtk_audioplayer.c
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef unsigned char u8 ;
typedef unsigned short u16 ;
typedef unsigned char uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int u32 ;
typedef unsigned int uint ;
typedef unsigned int uint32 ;
typedef unsigned long long u64 ;
typedef unsigned long long uint64 ;
typedef unsigned int uint_t ;
typedef unsigned char uint8_t ;
typedef unsigned short uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned long long uint64_t ;
typedef unsigned int uint_t ;
typedef unsigned char uint_8 ;
typedef unsigned short uint_16 ;
typedef unsigned int uint_32 ;
typedef unsigned long long uint_64 ;
typedef signed char int8 ;
typedef signed short int16 ;
typedef signed int int32 ;
typedef signed int int_32 ;
typedef signed long long int64 ;
typedef signed char int8_t ;
typedef signed short int16_t ;
typedef signed int int32_t ;
typedef signed long long int64_t ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned int UINT ;
typedef unsigned int UINT32 ;
typedef unsigned long long UINT64 ;
typedef int INT ;
typedef char INT8 ;
typedef short INT16 ;
typedef int INT32 ;
typedef long long INT64 ;
typedef unsigned char U8 ;
typedef unsigned short U16 ;
typedef unsigned int U32 ;
typedef int S32 ;
typedef unsigned long long U64 ;
typedef char S8 ;
typedef short S16 ;
typedef long long S64 ;
typedef char s8 ;
typedef short s16 ;
typedef int s32 ;
typedef unsigned int size_t ;
typedef char ascii ;
typedef unsigned char byte ;
typedef unsigned short word ;
typedef unsigned long dword ;
typedef unsigned char BYTE ;
typedef char CHAR ;
typedef unsigned short WCHAR ;
typedef unsigned short WORD ;
typedef signed int WORD32 ;
typedef unsigned int UWORD32 ;
typedef unsigned short RESID ;
typedef float float32 ;
typedef float FLOAT ;
typedef double DOUBLE ;
typedef UINT8* PUINT8 ;
typedef INT32* PINT32 ;
typedef UINT16* PUINT16 ;
typedef INT16* PINT16 ;
typedef CHAR * PCHAR ;
typedef void* PVOID ;
typedef char * PS8 ;
typedef unsigned char * PU8 ;
typedef short * PS16 ;
typedef unsigned short * PU16 ;
typedef int * PS32 ;
typedef unsigned int * PU32 ;
typedef unsigned short pBOOL ;
typedef volatile unsigned char REG8 ;
typedef volatile unsigned short REG16 ;
typedef volatile unsigned int REG32 ;
typedef unsigned char kal_uint8 ;
typedef signed char kal_int8 ;
typedef char kal_char ;
typedef unsigned short kal_wchar ;
typedef unsigned short int kal_uint16 ;
typedef signed short int kal_int16 ;
typedef unsigned int kal_uint32 ;
typedef signed int kal_int32 ;
typedef unsigned int HRES ;
typedef unsigned int HAO ;
typedef unsigned char u8_t ;
typedef unsigned short u16_t ;
typedef u32 mbtk_mutex ;
typedef u32 mbtk_sema ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef char CHAR ;
typedef signed short INT16 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef void* mbtk_taskref ;
typedef void* mbtk_hisrref ;
typedef void* mbtk_msgqref ;
typedef void* mbtk_mailboxqref ;
typedef void* mbtk_semref ;
typedef void* mbtk_mutexref ;
typedef void* mbtk_flagref ;
typedef void* mbtk_osmemref ;
typedef void* mbtk_ostimerref ;
typedef void *mbtk_osref ;
typedef uint8_t mbtk_os_status ;
typedef va_list __gnuc_va_list ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_INT_IFC ,	 
 DIAG_EXT_IFC	 
 } DIAG_IF_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_DEV_USB ,	 
 DIAG_DEV_SD ,	 
 DIAG_DEV_FS ,	 
 DIAG_DEV_UART ,	 
 DIAG_DEV_SPI ,	 
 DIAG_DEV_NONE	 
 } DIAG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 SULOG_DEV_USB ,	 
 SULOG_DEV_SD	 
 } SULOG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 EEH_DUMP_DEV_USB_SD ,	 
 EEH_DUMP_DEV_SPI	 
 } EEH_DUMP_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_START_PS_OFF ,	 
 DIAG_START_PS_ON	 
 } DIAG_START_PS_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_UART_SPEED_921600 ,	 
 DIAG_UART_SPEED_1842000 ,	 
 DIAG_UART_SPEED_3000000 ,	 
 DIAG_UART_DISABLE ,	 
 } DIAG_UART_SPEED_TYPE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 DIAG_IF_TYPE useIntIf ; /* use internal interface or external interface */	 
 DIAG_UART_SPEED_TYPE useHighSpeedUART ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL GLFeatureFlag ;	 
 DIAG_START_PS_TYPE diagStartPS ;	 
 DIAG_DEV_TYPE diagDevType ;	 
 SULOG_DEV_TYPE sulogDevType ;	 
 EEH_DUMP_DEV_TYPE eehDumpDevType ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL usbUserMode ;	 
 BOOL sdlAutoDelete ;	 
 } diagCfgDataS;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT32 dbID ;	 
 UINT32 filterBitLength ;	 
 UINT32 reserved [ 6 ] ;	 
 } DIAG_Nvm_Filter_File_Header_t;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 YMODEM_DISABLE = 0x0 ,	 
 YMODEM_ENABLE = 0x1	 
 } Ymodem_Dump_config;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Ymodem_Dump_config config ;	 
 } Ymodem_Dump_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 /* MIFI driver*/	 
 USB_GENERIC_MIFI_DRIVER = 0x0 ,	 
 USB_MARVELL_MIFI_DRIVER = 0x1 ,	 
 USB_ASR_MIFI_DRIVER = 0x2 ,	 
 USB_GENERIC_MOD_DRIVER = 0x10 ,	 
 USB_GENERIC_MOD_ECM_DRIVER = 0x12 ,	 
 USB_DIAG_UAC_DRIVER = 0x14 ,	 
	 
 /* MBIM driver*/	 
 USB_MBIM_ONLY_DRIVER = 0x40 ,	 
 USB_MBIM_GENERIC_DRIVER = 0x41 ,	 
 USB_MBIM_MAX_DRIVER = 0x4F ,	 
	 
 /* Other driver*/	 
 USB_CDROM_ONLY_DRIVER = 0x91 ,	 
 USB_CDROM_DIAG_DRIVER = 0x92 ,	 
 USB_DIAG_ONLY_DRIVER = 0x93 ,	 
 USB_MODEM_ONLY_DRIVER = 0x94 ,	 
 USB_MODEM_DIAG_DRIVER = 0x95 ,	 
	 
 USB_MAX_DRIVER = 0xFF	 
 } Usb_driver_typeE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 MASS_STORAGE_DISABLE = 0x0 ,	 
 MASS_STORAGE_ENABLE = 0x1	 
 } MassStorage_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_AUTO_INSTALL_DISABLE = 0x0 ,	 
 USB_AUTO_INSTALL_ENABLE = 0x1	 
 } Usb_auto_install_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_OS_DETECT_DISABLE = 0x0 ,	 
 USB_OS_DETECT_ENABLE = 0x1	 
 } Usb_OS_detect_type;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Usb_driver_typeE usb_driver ;	 
 MassStorage_ConfigE mass_storage ;	 
 Usb_auto_install_type auto_install ;	 
 Usb_OS_detect_type os_detect ;	 
 } Usb_DriverS;

typedef void ( * MBTK_AUDIO_PA_HOOK ) ( int enable ) ;
typedef void ( * MBTK_AUDIO_PLAYER_CALLBACK ) ( void *param ) ;
typedef void ( *MBTK_AUDIO_RECORD_CALLBACK ) ( MBTK_MCI_EVNET event , MBTK_MCI_INFO info_type , int value ) ;
typedef void ( *mbtk_mp3_play_cb ) ( int ) ;
typedef int ( *audio_process_cb ) ( char *in_buf , int in_lens , char *out_buf , int *out_lens , int samperate , int channel , int bits ) ;
typedef void ( *mbtk_amr_play_cb ) ( int ) ;
typedef int ( *MCI_AUDIO_BUFFER_PLAY_DATA_CALLBACK_T ) ( unsigned int from_pos , unsigned char *data , unsigned int size ) ;
typedef void ( *play_ev_cb ) ( int status ) ;
typedef void ( *player_process_cb ) ( int process ) ;
typedef UINT8 BOOL ;
typedef void ( *MP3_EVENT_CB ) ( int ) ;
typedef void ( *MBTK_AUDIO_CONTINUE_RECORD_CALLBACK ) ( const char* , int ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\AudioExtern.ppp
//PPL Source File Name : \\hop\\bsp\\src\\AudioExtern.c
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PMU_POR = 1 ,	 
 PMU_EMR ,	 
 PMU_WDTR = ( PMU_EMR+2 )	 
 } PMU_LastResetStatus;

typedef UINT8 UART_Activity ;
//ICAT EXPORTED STRUCT 
 typedef struct /* This is structure of the UART Configuration */ 
 {	 
 UART_OpMode opMode ; /* fifo mode , non fifo mode or DMA for basic interface*/	 
 UART_TriggerLevel triggerLevel ; /* the trigger level interrupt on 1 , 8 , 16 , 32 */	 
 UART_BaudRates baudRate ; /* the rate of the transmit and the receive up to 111520 ( default - 9600 ) .*/	 
 UART_WordLen numDataBits ; /* 5 , 6 , 7 , or 8 number of data bits in the UART data frame ( default - 8 ) . */	 
 UART_StopBits stopBits ; /* 1 , 1.500000 or 2 stop bits in the UART data frame ( default - 1 ) . */	 
 UART_ParityTBits parityBitType ; /* Even , Odd or no-parity bit type in the UART data frame ( default - Non ) . */	 
 UART_InterfaceType interfaceType ; /* number of interface that the UART driver supplies ( default - UART_IF_TYPE_L2 ) */	 
 BOOL modemSignal ; /* enable operate modem - TRUE , disable modem - FALSE */	 
 BOOL flowControl ; /* enable Auto flow Control - TRUE , disable Auto flow Control - FALSE */	 
 UINT8 sleepMode ; /* enable sleep mode - TRUE , more fine control - see UARTSleepMode enum */	 
 BOOL auto_baud ; /* enable auto_baud , auto-baud-rate detection within the UART ( default - FALSE ) */	 
 UART_SIRConfigure sirIrDA ;	 
 } UARTConfiguration;

//ICAT EXPORTED ENUM 
 typedef enum // change the order -1 to + 
 {	 
 UART_RC_OK = 1 , /* 1 - no errors */	 
	 
 UART_RC_PORT_NUM_ERROR = -100 , /* -100 - Error in the UART port number */	 
 UART_RC_NO_DATA_TO_READ , /* -99 - Eror no data to read from the FIFO UART */	 
 UART_RC_ILLEGAL_BAUD_RATE , /* -98 - Error in the UART Bayd Rate */	 
 UART_RC_UART_PARITY_BITS_ERROR , /* -97 - Error in parity bit */	 
 UART_RC_UART_ONE_STOP_BIT_ERROR , /* -96 - Error in one stop bit */	 
 UART_RC_ONE_HALF_OR_TWO_STOP_BIT_ERROR , /* -95 - Error in two stop bit */	 
 UART_RC_BAD_INTERFACE_TYPE , /* -94 - Error in the Interface Type */	 
 UART_RC_UART_NOT_AVAILABLE , /* -93 - Error in try to open UART that is open */	 
 UART_RC_NO_DATA_TO_WRITE , /* -92 - Error No data to writ the len = 0 */	 
 UART_RC_NOT_ALL_BYTE_WRITTEN , /* -91 - Error Not all the Byte write to the UART FIFO */	 
 UART_RC_ISR_ALREADY_BIND , /* -90 - Error try to bind ISR for Basic Interface */	 
 UART_RC_WRONG_ISR_UNBIND , /* -89 - Error in the UnBind ISR for Basic Interface */	 
 UART_RC_FIFO_NOT_EMPTY , /* -88 - Error , the UART FIFO not empty */	 
 UART_RC_UART_OPEN , /* -87 - Error try chance the configurr when the UART open */	 
 UART_RC_GPIO_ERR , /* -86 - Error in the Configure of the GPIO */	 
 UART_RC_IRDA_CONFIG_ERR , /* -85 - Illegal IrDA configuration */	 
 UART_RC_TX_DMA_ERR /* -84 - DMA TX Error */	 
 } UART_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 LOG_DISABLE = 0x0 ,	 
 UART_LOG_ENABLE = 0x1 ,	 
 ACAT_LOG_ENABLE = 0x2	 
 } Log_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 MSG_DISABLE = 0x0 ,	 
 ACAT_MSG_ENABLE = 0x1	 
 } Msg_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RTI_LOG_DISABLE = 0x0 ,	 
 RTI_DUMP_ENABLE = 0x1 ,	 
 RTI_TASK_ENABLE = 0x2 ,	 
 RTI_MIPS_ENABLE = 0x3	 
 } RTI_ConfigE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Log_ConfigE log_cfg ;	 
 Msg_ConfigE msg_cfg ;	 
 RTI_ConfigE rti_cfg ;	 
 } Log_ConfigS;

typedef void ( *UARTNotifyInterrupt ) ( UART_Port ) ;
typedef void ( *UsbLogPrint_t ) ( const char * , ... ) ;
DIAG_FILTER ( AUDIO , Voice , audioGsmCB_NULL , DIAG_ERROR)  
 diagTextPrintf ( " audioGsmCB_NULL " );

//ICAT EXPORTED FUNCTION - Audio , Common , audioPhase1Init 
 void audioPhase1Init ( void ) 
 {	 
 if ( !IsMiniSystem ( ) )	 
 {		 
 audioPhase1Init_internal ( ) ;		 
 }	 
 else	 
 {		 
 Audio_Init_FakeBind ( ) ;		 
 }	 
 }

//ICAT EXPORTED FUNCTION - Audio , Common , audioPhase2Init 
 void audioPhase2Init ( void ) 
 {	 
 if ( !IsMiniSystem ( ) )	 
 {		 
 audioPhase2Init_internal ( ) ;		 
 }	 
 }

//ICAT EXPORTED FUNCTION - Audio , Voice , amrResume 
 void amrResume ( void ) 
 {	 
 if ( !IsMiniSystem ( ) )	 
 {		 
 amrResume_internal ( ) ;		 
 }	 
 }

//ICAT EXPORTED FUNCTION - Audio , Voice , amrSuspend 
 void amrSuspend ( void ) 
 {	 
 if ( !IsMiniSystem ( ) )	 
 {		 
 amrSuspend_internal ( ) ;		 
 }	 
 }

//ICAT EXPORTED FUNCTION - ADEMO , Voice , LteVoiceResume 
 void LteVoiceResume ( ) // LTE handover / reselect to GSM / UMTS fails || GSM / UMTS handover to LTE 
 {	 
 if ( !IsMiniSystem ( ) )	 
 {		 
 LteVoiceResume_internal ( ) ;		 
 }	 
 }

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbtk_audio_acm.ppp
//PPL Source File Name : \\mbtk\\wav\\src\\mbtk_audio_acm.c
typedef void ( *mbtk_oem_RecordCB ) ( const char* data , int length ) ;
typedef void ( *mbtk_oem_PlayCB ) ( int rest_data ) ;
typedef unsigned char u8 ;
typedef unsigned short u16 ;
typedef unsigned char uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int u32 ;
typedef unsigned int uint ;
typedef unsigned int uint32 ;
typedef unsigned long long u64 ;
typedef unsigned long long uint64 ;
typedef unsigned int uint_t ;
typedef unsigned char uint8_t ;
typedef unsigned short uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned long long uint64_t ;
typedef unsigned int uint_t ;
typedef unsigned char uint_8 ;
typedef unsigned short uint_16 ;
typedef unsigned int uint_32 ;
typedef unsigned long long uint_64 ;
typedef signed char int8 ;
typedef signed short int16 ;
typedef signed int int32 ;
typedef signed int int_32 ;
typedef signed long long int64 ;
typedef signed char int8_t ;
typedef signed short int16_t ;
typedef signed int int32_t ;
typedef signed long long int64_t ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned int UINT ;
typedef unsigned int UINT32 ;
typedef unsigned long long UINT64 ;
typedef int INT ;
typedef char INT8 ;
typedef short INT16 ;
typedef int INT32 ;
typedef long long INT64 ;
typedef unsigned char U8 ;
typedef unsigned short U16 ;
typedef unsigned int U32 ;
typedef int S32 ;
typedef unsigned long long U64 ;
typedef char S8 ;
typedef short S16 ;
typedef long long S64 ;
typedef char s8 ;
typedef short s16 ;
typedef int s32 ;
typedef unsigned int size_t ;
typedef char ascii ;
typedef unsigned char byte ;
typedef unsigned short word ;
typedef unsigned long dword ;
typedef unsigned char BYTE ;
typedef char CHAR ;
typedef unsigned short WCHAR ;
typedef unsigned short WORD ;
typedef signed int WORD32 ;
typedef unsigned int UWORD32 ;
typedef unsigned short RESID ;
typedef float float32 ;
typedef float FLOAT ;
typedef double DOUBLE ;
typedef UINT8* PUINT8 ;
typedef INT32* PINT32 ;
typedef UINT16* PUINT16 ;
typedef INT16* PINT16 ;
typedef CHAR * PCHAR ;
typedef void* PVOID ;
typedef char * PS8 ;
typedef unsigned char * PU8 ;
typedef short * PS16 ;
typedef unsigned short * PU16 ;
typedef int * PS32 ;
typedef unsigned int * PU32 ;
typedef unsigned short pBOOL ;
typedef volatile unsigned char REG8 ;
typedef volatile unsigned short REG16 ;
typedef volatile unsigned int REG32 ;
typedef unsigned char kal_uint8 ;
typedef signed char kal_int8 ;
typedef char kal_char ;
typedef unsigned short kal_wchar ;
typedef unsigned short int kal_uint16 ;
typedef signed short int kal_int16 ;
typedef unsigned int kal_uint32 ;
typedef signed int kal_int32 ;
typedef unsigned int HRES ;
typedef unsigned int HAO ;
typedef unsigned char u8_t ;
typedef unsigned short u16_t ;
typedef u32 mbtk_mutex ;
typedef u32 mbtk_sema ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef uint32_t acm_audio_track_handle ;
typedef void ( *acm_audio_track_event_callback_t ) ( acm_audio_track_handle , acm_audio_track_event_t ) ;
typedef acm_audio_track_handle audio_track_handle ;
typedef uint32_t acm_audio_record_handle ;
typedef acm_audio_record_handle audio_record_handle ;
typedef void ( *acm_audio_record_data_callback_t ) ( acm_audio_record_handle , const int16_t* data , uint32_t size ) ;
typedef void ( *acm_audio_record_event_callback_t ) ( acm_audio_record_handle , acm_audio_record_event_t ) ;
typedef unsigned int size_t ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef char CHAR ;
typedef signed short INT16 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef uint32_t audio_effect_handle ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_INT_IFC ,	 
 DIAG_EXT_IFC	 
 } DIAG_IF_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_DEV_USB ,	 
 DIAG_DEV_SD ,	 
 DIAG_DEV_FS ,	 
 DIAG_DEV_UART ,	 
 DIAG_DEV_SPI ,	 
 DIAG_DEV_NONE	 
 } DIAG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 SULOG_DEV_USB ,	 
 SULOG_DEV_SD	 
 } SULOG_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 EEH_DUMP_DEV_USB_SD ,	 
 EEH_DUMP_DEV_SPI	 
 } EEH_DUMP_DEV_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_START_PS_OFF ,	 
 DIAG_START_PS_ON	 
 } DIAG_START_PS_TYPE;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 DIAG_UART_SPEED_921600 ,	 
 DIAG_UART_SPEED_1842000 ,	 
 DIAG_UART_SPEED_3000000 ,	 
 DIAG_UART_DISABLE ,	 
 } DIAG_UART_SPEED_TYPE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 DIAG_IF_TYPE useIntIf ; /* use internal interface or external interface */	 
 DIAG_UART_SPEED_TYPE useHighSpeedUART ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL GLFeatureFlag ;	 
 DIAG_START_PS_TYPE diagStartPS ;	 
 DIAG_DEV_TYPE diagDevType ;	 
 SULOG_DEV_TYPE sulogDevType ;	 
 EEH_DUMP_DEV_TYPE eehDumpDevType ;	 
 // DIAG_MEM_SWITCH diagMemSwitch ;	 
 BOOL usbUserMode ;	 
 BOOL sdlAutoDelete ;	 
 } diagCfgDataS;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT32 dbID ;	 
 UINT32 filterBitLength ;	 
 UINT32 reserved [ 6 ] ;	 
 } DIAG_Nvm_Filter_File_Header_t;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 YMODEM_DISABLE = 0x0 ,	 
 YMODEM_ENABLE = 0x1	 
 } Ymodem_Dump_config;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Ymodem_Dump_config config ;	 
 } Ymodem_Dump_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 /* MIFI driver*/	 
 USB_GENERIC_MIFI_DRIVER = 0x0 ,	 
 USB_MARVELL_MIFI_DRIVER = 0x1 ,	 
 USB_ASR_MIFI_DRIVER = 0x2 ,	 
 USB_GENERIC_MOD_DRIVER = 0x10 ,	 
 USB_GENERIC_MOD_ECM_DRIVER = 0x12 ,	 
 USB_DIAG_UAC_DRIVER = 0x14 ,	 
	 
 /* MBIM driver*/	 
 USB_MBIM_ONLY_DRIVER = 0x40 ,	 
 USB_MBIM_GENERIC_DRIVER = 0x41 ,	 
 USB_MBIM_MAX_DRIVER = 0x4F ,	 
	 
 /* Other driver*/	 
 USB_CDROM_ONLY_DRIVER = 0x91 ,	 
 USB_CDROM_DIAG_DRIVER = 0x92 ,	 
 USB_DIAG_ONLY_DRIVER = 0x93 ,	 
 USB_MODEM_ONLY_DRIVER = 0x94 ,	 
 USB_MODEM_DIAG_DRIVER = 0x95 ,	 
	 
 USB_MAX_DRIVER = 0xFF	 
 } Usb_driver_typeE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 MASS_STORAGE_DISABLE = 0x0 ,	 
 MASS_STORAGE_ENABLE = 0x1	 
 } MassStorage_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_AUTO_INSTALL_DISABLE = 0x0 ,	 
 USB_AUTO_INSTALL_ENABLE = 0x1	 
 } Usb_auto_install_type;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 USB_OS_DETECT_DISABLE = 0x0 ,	 
 USB_OS_DETECT_ENABLE = 0x1	 
 } Usb_OS_detect_type;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Usb_driver_typeE usb_driver ;	 
 MassStorage_ConfigE mass_storage ;	 
 Usb_auto_install_type auto_install ;	 
 Usb_OS_detect_type os_detect ;	 
 } Usb_DriverS;

DIAG_FILTER ( AUDIO , TRACK_CLIENT , mbtk_track_client_event_callback_1 , DIAG_INFORMATION)  
 diagPrintf ( " ignore an event callback cause flag ref have not been created " );

DIAG_FILTER ( AUDIO , TRACK_CLIENT , destroy_mbtk_track_client_task , DIAG_INFORMATION)  
 diagPrintf ( " mbtk_track_client_task_stack:0x%lx " , mbtk_track_client_task_stack );

//ICAT EXPORTED FUNCTION - Audio , mbtk_track , create_mbtk_track_client_task_env 
 void create_mbtk_track_client_task ( void ) {	 
DIAG_FILTER ( AUDIO , TRACK_CLIENT , create_mbtk_track_client_task , DIAG_INFORMATION)  
 diagPrintf ( " mbtk_track_client_task_stack:0x%lx " , mbtk_track_client_task_stack );

	 
 if ( !mbtk_track_client_task_stack )	 
 mbtk_track_client_task_stack = alignMalloc ( 2048 ) ;	 
 if ( !mbtk_track_client_flag_ref )	 
 OsaFlagCreate ( &mbtk_track_client_flag_ref , 0 ) ;	 
 if ( !mbtk_track_client_task_ref )	 
 OSATaskCreate ( &mbtk_track_client_task_ref ,	 
 mbtk_track_client_task_stack ,	 
 2048 ,	 
 ( 79 ) ,	 
 " audio_mbtk_track_client " ,	 
 audio_mbtk_track_client_main_loop ,	 
 0 ) ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , mbtk_track , destroy_mbtk_track_client_task_env 
 void destroy_mbtk_track_client_task_env ( void ) {	 
 destroy_mbtk_track_client_task ( 1 ) ;	 
 }

DIAG_FILTER ( AUDIO , TRACK_CLIENT , mbtk_track_play_stop , DIAG_INFORMATION)  
 diagPrintf ( " id:%ld , drain:%ld " , id , drain );

DIAG_FILTER ( AUDIO , TRACK_CLIENT , mbtk_track_play_pause , DIAG_INFORMATION)  
 diagPrintf ( " id:%ld , pause:%ld " , id , pause_ctrl );

DIAG_FILTER ( AUDIO , TRACK_CLIENT , mbtk_track_play_mute , DIAG_INFORMATION)  
 diagPrintf ( " id:%ld , mute:%ld " , id , mute_ctrl );

DIAG_FILTER ( MBTK , ACM , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

DIAG_FILTER ( MBTK , ACM , DEBUG , DIAG_INFORMATION)  
 diagPrintf ( " %s " , mlog_buffer );

