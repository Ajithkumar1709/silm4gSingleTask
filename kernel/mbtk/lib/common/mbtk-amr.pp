//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\amr_vocoder_api.ppppp
//PPL Source File Name : \\mbtk\\amr\\src\\amr_vocoder_api.cpp
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
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef ::std:: va_list __gnuc_va_list ;
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
typedef unsigned int ACM_AudioConfirmID ;
typedef unsigned int ACM_MSAGain ;
typedef unsigned int ACM_AudioMISC ;
typedef signed char ACM_DigitalGain ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_MUTE_OFF = 0 ,	 
 ACM_MUTE_ON = 1 ,	 
	 
 ACM_AUDIO_MUTE_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_AudioMute;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ATC_DEFAULT = 0 ,	 
 ATC_HANDSET ,	 
 ATC_HEADSET ,	 
 ATC_HANDSFREE ,	 
 ATC_BLUETOOTH ,	 
 ATC_STEREO_BT ,	 
 ATC_SPEAKERPHONE ,	 
 ATC_HEADPHONE ,	 
 ATC_BT_NREC_OFF ,	 
 ATC_BT_WB ,	 
 ATC_BT_NREC_OFF_WB ,	 
 ATC_HANDSET_DUALMIC ,	 
 ATC_HEADSET_DUALMIC ,	 
 ATC_HANDSFREE_DUALMIC ,	 
 ATC_HANDSET_EXTRAVOL_ON ,	 
 ATC_HANDSFREE_EXTRAVOL_ON ,	 
 ATC_HANDSET_DUALMIC_EXTRAVOL_ON ,	 
 ATC_HANDSFREE_DUALMIC_EXTRAVOL_ON ,	 
	 
 ATC_TTY ,	 
 ATC_TTY_HCO ,	 
 ATC_TTY_VCO ,	 
 ATC_TTY_VCO_DUALMIC ,	 
	 
 ATC_HANDSET_LOOP ,	 
 ATC_HEADSET_LOOP ,	 
 ATC_HANDSFREE_LOOP ,	 
 ATC_HEADPHONE_LOOP ,	 
 ATC_STEREO_BT_LOOP ,	 
	 
 ATC_HANDSET_ENH_OFF ,	 
 ATC_HEADSET_ENH_OFF ,	 
 ATC_HANDSFREE_ENH_OFF ,	 
 ATC_HEADPHONE_ENH_OFF ,	 
 ATC_STEREO_BT_ENH_OFF ,	 
	 
 ATC_FM ,	 
	 
 ATC_PATH_NUM	 
 } ATCPath;

typedef ATCHandshakeExecMsg ATCHandshakeCfmMsg ;
typedef ATCPCMRecStrmIndiMsg ATCPCMPlayStrmRspMsg ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_RC_OK = 1 ,	 
 ACM_RC_DEVICE_ALREADY_ENABLED ,	 
 ACM_RC_DEVICE_ALREADY_DISABLED ,	 
 ACM_RC_NO_MUTE_CHANGE_NEEDED ,	 
 ACM_RC_INVALID_VOLUME_CHANGE ,	 
 ACM_RC_DEVICE_NOT_FOUND ,	 
 ACM_RC_BUFFER_GET_FUNC_INVALID ,	 
 ACM_RC_STREAM_OUT_NOT_PERFORMED ,	 
 ACM_RC_STREAM_IN_NOT_PERFORMED ,	 
 ACM_RC_STREAM_OUT_TO_BE_STOPPED_NOT_ACTIVE ,	 
 ACM_RC_STREAM_IN_TO_BE_STOPPED_NOT_ACTIVE ,	 
 ACM_RC_I2S_INVALID_DATA_POINTER ,	 
 ACM_RC_I2S_INVALID_DATA_SIZE ,	 
 ACM_RC_I2S_INVALID_NOTIFICATION_THRESHOLD ,	 
 ACM_RC_I2S_MESSAGE_QUEUE_IS_FULL ,	 
 ACM_RC_MEMORY_ALREADY_INITIALISED ,	 
	 
 //// Jackie add	 
 ACM_RC_NEED_DISABLE_PATH , // need APPS to disable codec path	 
 ACM_RC_MALLOC_ERROR , // memory error	 
 ACM_RC_OUTOF_RANGE ,	 
	 
 /* Must be at the end */	 
 ACM_RC_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_ReturnCode;

typedef UINT32 PM_TimeIn32KHzUnitsT ;
//ICAT EXPORTED ENUM 
 typedef enum {	 
 PM_EXT_DBG_EVENT_EMPTY = 0 ,	 
 PM_EXT_DBG_EVENT_GENERAL_PURPOSE = 99 , // for debug purposes , general event to	 
 // track something while debug ( not to be left in code permanently ) !	 
 PM_EXT_DBG_EVENT_D2_EXIT =100 , // 100	 
 PM_EXT_DBG_EVENT_C1_EXIT , // 101	 
 PM_EXT_DBG_EVENT_C1_GATED_EXIT , // 102	 
 PM_EXT_DBG_EVENT_TM_GET_NEAREST , // 103	 
 PM_EXT_DBG_EVENT_TM_SUSPEND , // 104	 
 PM_EXT_DBG_EVENT_TM_SYNCH_AFTER , // 105	 
 PM_EXT_DBG_EVENT_TM_NU_TICK , // 106	 
 PM_EXT_DBG_EVENT_TM_EXT_TICK , // 107	 
 PM_EXT_DBG_EVENT_TM_SKIP_OS_TICK , // 108	 
 PM_EXT_DBG_EVENT_TM_SUSPEND_ENABLE , // 109	 
 PM_EXT_DBG_EVENT_TM_SUSPEND_DISABLE , // 110	 
 PM_EXT_DBG_EVENT_TM_TRIGGER_ERROR , // 111	 
 PM_EXT_DBG_EVENT_TICK_FROM_SYNCH , // 112	 
 PM_EXT_DBG_EVENT_TICK_FROM_TRIGGER , // 113	 
 PM_EXT_DBG_EVENT_TM_HW_TIMER_SET , // 114	 
 PM_EXT_DBG_EVENT_OS_TIMER_EXPIRE , // 115	 
 PM_EXT_DBG_EVENT_TM_TICK_SUSPENDED , // 116	 
 PM_EXT_DBG_EVENT_ACTIVATE_NU_HISR , // 117	 
 PM_EXT_DBG_EVENT_ACTIVATE_GKI_HISR , // 118	 
 PM_EXT_DBG_EVENT_TIMER_DEACTIVATE , // 119	 
 PM_EXT_DBG_EVENT_TIMER_CONFIGURE , // 120	 
 PM_EXT_DBG_EVENT_TIMER_ACTIVATE , // 121	 
 PM_EXT_DBG_EVENT_TIMER_STATUS_CLEAR , // 122	 
 PM_EXT_DBG_EVENT_TIMER_TCMR_SET , // 123	 
 PM_EXT_DBG_EVENT_TIMER_STATUS_READ , // 124	 
 PM_EXT_DBG_EVENT_TIMER_TIER_CLEAR , // 125	 
 PM_EXT_DBG_EVENT_TIMER_TMR_SET , // 126	 
 PM_EXT_DBG_EVENT_TIMER_TCCR_SET , // 127	 
 PM_EXT_DBG_EVENT_TIMER_TIER_SET , // 128	 
 PM_EXT_DBG_EVENT_RM_PREVENT_D2 , // 129	 
 PM_EXT_DBG_EVENT_AAM_PREVENT_D2 , // 130	 
 PM_EXT_DBG_EVENT_GP_FLAG_1 , // 131	 
 PM_EXT_DBG_EVENT_AAM_D2_TIMER_WAKEUP , // 132	 
 PM_EXT_DBG_EVENT_AAM_D2_OWN_WAKEUP , // 133	 
 PM_EXT_DBG_EVENT_AAM_MANAGE_BUSY , // 134	 
 PM_EXT_DBG_EVENT_AAM_MANAGE_FREE , // 135	 
 PM_EXT_DBG_EVENT_AAM_ALLOW_D2 , // 136	 
 PM_EXT_DBG_EVENT_AAM_AA_FORBID_D2 , // 137	 
 PM_EXT_DBG_EVENT_AAM_TM_FORBID_D2 , // 138	 
 PM_EXT_DBG_EVENT_AAM_APP_TM_D2 , // 139	 
 PM_EXT_DBG_EVENT_AAM_OST_TM_D2 , // 140	 
 PM_EXT_DBG_EVENT_RM_TCU_ALLOC , // 141	 
 PM_EXT_DBG_EVENT_RM_TCU_FREE , // 142	 
 PM_EXT_DBG_EVENT_RM_SCK_ALLOC , // 143	 
 PM_EXT_DBG_EVENT_RM_SCK_FREE , // 144	 
 PM_EXT_DBG_EVENT_RM_ALLOW_D2 , // 145	 
 PM_EXT_DBG_EVENT_RM_FORBID_D2 , // 146	 
 PM_EXT_DBG_EVENT_RM_ALLOW_C1_GATED , // 147	 
 PM_EXT_DBG_EVENT_TCU_D2_PREPARE , // 148	 
 PM_EXT_DBG_EVENT_TCU_D2_RECOVER , // 149	 
 PM_EXT_DBG_EVENT_CPA_D2_PREPARE , // 150	 
 PM_EXT_DBG_EVENT_CPA_D2_RECOVER , // 151	 
 PM_EXT_DBG_EVENT_CPA_D2_WAKEUP , // 152	 
 PM_EXT_DBG_EVENT_D2_WAKEUP_TIMER , // 153	 
 PM_EXT_DBG_EVENT_GSM_WAKEUP_SWI , // 154	 
 PM_EXT_DBG_EVENT_GSM_SLEEP_SWI , // 155	 
 ////////////////////////////////////////////// DDR	 
 PM_EXT_DBG_EVENT_CHANGED_TO_WAIT_FOR_DDR_HIGH_FREQ_ACK_WHILE_RELINQUISH_HIGH_IS_PENDING ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_WAIT_FOR_DDR_REQUEST_ACK ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_SYSTEM_IN_REG_RUNNING_MODE_AND_SEND_REQ ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_WAIT_FOR_DDR_REQUEST_ACK_WHILE_HIGH_IS_PENDING ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_WAIT_FOR_DDR_HIGH_FREQ_ACK ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_WAIT_FOR_DDR_HIGH_FREQ_ACK_AND_SEND_REQ ,	 
 PM_EXT_DBG_EVENT_CHANGED_TO_SYSTEM_IN_REG_RUNNING_MODE ,	 
 PM_EXT_DBG_EVENT_AC_IPC_INTERRUPT_HANDLER ,	 
 PM_EXT_DBG_EVENT_260_REL_ACK ,	 
 PM_EXT_DBG_EVENT_CHANGED_SYSTEM_IN_HIGH_FREQ_MODE ,	 
 PM_EXT_DBG_EVENT_DDR_REG_REQ ,	 
 PM_EXT_DBG_EVENT_DDR_REG_RELINQUISH ,	 
 PM_EXT_DBG_EVENT_DDR_REG_REQ_AND_RELINQUISH ,	 
 PM_EXT_DBG_EVENT_DDR_HF_REQ ,	 
 PM_EXT_DBG_EVENT_DDR_HF_RELINQUISH ,	 
 PM_EXT_DBG_EVENT_DDR_HF_REQ_AND_RELINQUISH ,	 
	 
 PM_EXT_DBG_EVENT_DDR_STATUS_FORBID_D2 ,	 
 ////////////////////////////////////////////// DDR	 
	 
 PM_EXT_DBG_EVENT_RM_ALLOC ,	 
 PM_EXT_DBG_EVENT_RM_FREE ,	 
	 
 PM_EXT_DBG_EVENT_D2_ENTRY ,	 
 PM_EXT_DBG_EVENT_C1_ENTRY ,	 
 PM_EXT_DBG_EVENT_C1_GATED_ENTRY ,	 
 PM_EXT_DBG_EVENT_D0CS_ENTRY ,	 
 PM_EXT_DBG_EVENT_D0CS_EXIT ,	 
 // BRN	 
 PM_EXT_DBG_EVENT_VCTCXO_RELINQUISH ,	 
 PM_EXT_DBG_EVENT_VCTCXO_REQUEST ,	 
 PM_EXT_DBG_EVENT_DDR_LPM_DONE ,	 
 PM_EXT_DBG_EVENT_POUT_DISABLE ,	 
 PM_EXT_DBG_EVENT_POUT_ENABLE ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_HIGH ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_LOW ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_USER ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_START ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_DONE ,	 
 PM_EXT_DBG_EVENT_FREQ_CHANGE_GET_FREQ ,	 
 PM_EXT_DBG_EVENT_DVFM_TABLE_UPDATE ,	 
 PM_EXT_DBG_EVENT_LPM_DECISION ,	 
 PM_EXT_DBG_EVENT_SRAM_MEMORY_ERRORS_COUNT ,	 
 PM_EXT_DBG_WAKEUP_SRC ,	 
 PM_EXT_DBG_WAKEUP_SRC_NOTREGISTER ,	 
 PM_EXT_DBG_EVENT_NO_DATA = 1500 , /* indicates that no data is send with the event	 
 ( and forces the enum to be treated as UINT32 ) */	 
 PM_EXT_DBG_DATA_FAKE_D2 =0x2000000 , //	 
 PM_EXT_DBG_DATA_REAL_D2 =0x4000000 // we add to this bit hte wakeup event register	 
 // - relevant bits are 0 -19	 
 } PM_EventTypeE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 PM_TimeIn32KHzUnitsT timeStamp ;	 
 PM_EventTypeE event ;	 
 UINT32 data ;	 
 } PM_TimeStampLogEnteryS;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 UINT32 nextEntryIndex ;	 
 PM_TimeStampLogEnteryS eventLog [ 256 ] ;	 
 BOOL logEnabled ;	 
 BOOL cyclic ;	 
 } PM_EventLogS;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 COMMPM_PP_NOTSET ,	 
 COMMPM_PP_1 ,	 
 COMMPM_PP_2 ,	 
 COMMPM_PP_3 ,	 
 COMMPM_PP_4 ,	 
 COMMPM_NUMBER_OF_PP = 4	 
 } CommPM_PPE;

typedef void ( *COMMPM_DDRAckNotificationT ) ( CommPM_DDRAckE ackType ) ;
typedef void ( *COMMPM_DDRDVFMNotificationT ) ( CommPM_PPE PPType ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 Service_UART = 0x01 ,	 
 Enable_TCU_clock= 0x02 ,	 
 Service_HSPDA = 0x04 ,	 
 Service_ICAT = 0x08 ,	 
 Service_client5 = 0x10 ,	 
 Service_client6 = 0x20 ,	 
 Service_client7 = 0x40 ,	 
 Service_client8 = 0x80	 
	 
 } CommPM_servicesD1E;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 COMMPM_MODEM_ENABLE = 0 ,	 
 COMMPM_MODEM_DISABLE ,	 
 COMMPM_INVALID_STATE	 
	 
 } PM_Modem_StateE;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT32 D2mode ; // 0 - no D2 , 1 - D2 alike , 2 - full D2	 
 UINT32 D2Variation ; // 0 Stay in D0 , 1 , go to C1 , 2 Full D2	 
 UINT32 LPTsleepTicks ; // how many ticks the LPT should sleep	 
 // temp solution for L1 Standalone.	 
 UINT32 LPTdebugBusyWait ; // to enable time to enter commands when	 
 // waking up ( since currently ( Sep 6 ) at C1 / D2	 
 // we can not submit commands )	 
 UINT32 DDRFunctionalityIsOn ; // 0 -regular work without DDR / 1 -DDR functionality is open for debug / 2 -DDR full functionality	 
 UINT32 endlessLoopAfterD2nExit ;	 
 UINT32 endlessLoopAfterDDRgrantnTimes ;	 
 UINT32 kickWDTonD2Exit ;	 
 UINT16 ServiceD1control ; // word that indicates service controlling D1 , if bit is set , D1 should be prevented	 
 // ( the bit position is set by the enum CommPM_servicesD1E )	 
 UINT8 AppsCommSyncActivated ;	 
 BOOL allowC1 ; // when set real C1 from HW ( if D2 set , also C1 ? )	 
 BOOL notifyMSA ; // if set - we work with L1 , and should notify them	 
 // otherwise we are in ' D2 standalone ' - only us	 
 BOOL LPTidle ; // LPT does nothing	 
 BOOL LPTdecisionOnly ; // do only decision no setting to HW , no prepare	 
 // ( means no real D2 , no C1 ) ( not relevant in LPTidle )	 
 // if not set - we have full LPT functionality	 
 BOOL L1isRegister ; // to synchronize D2 decisions on L1 registration	 
 BOOL PmDebugTaskEnalbe ; // to enable / disable comm pm debug task	 
 } CommPM_workModeS;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT32 DdrHfRequestTS ; // current client request TS ( maybe DDR in HF already )	 
 UINT32 DdrHfRequestFirstClientTS ; // signifies the first client request ( the one we wait for its ack )	 
 UINT32 DdrRegRequestTS ;	 
 UINT32 DdrRegMaxResponseTime ;	 
 UINT32 DdrHfClientTabResponseTime [ 30 ] ;	 
 UINT32 DdrRegClientTabResponseTime [ 30 ] ;	 
 UINT32 DdrHfMaxResponseTime ;	 
 } CommPM_DDRtimingS;

//ICAT EXPORTED ENUM 
 typedef enum {	 
 CommPM_Active ,	 
 CommPM_Idle ,	 
 COMMPM_NUMBER_OF_CPU_STATES ,	 
 } CommPM_CPUStateE;

typedef int ( *MMIC1PrepareFunc ) ( void ) ;
typedef int ( *MMIC1RecoverFunc ) ( void ) ;
typedef int ( *MMID2PrepareFunc ) ( void ) ;
typedef int ( *MMID2RecoverFunc ) ( BOOL ExitFromD2 ) ;
typedef int ( *MMIStatusFunc ) ( void ) ;
typedef UINT32 AAM_AppsStatusT ;
typedef UINT32 AAM_HandleT ;
typedef void ( AAM_CallbackFuncT ) ( void ) ;
typedef void ( AAM_CallbackFuncPrepareT ) ( PM_PowerStatesE statetoprepare ) ;
typedef void ( AAM_CallbackFuncRecoverT ) ( PM_PowerStatesE stateexited , BOOL b_DDR_ready , BOOL b_RegsRetainedState ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 /******************************************************************	 
 These ProcIDs are audio stub related	 
 *******************************************************************/	 
 // AUDIO_STUB_START_ID ,	 
 // AUDIO_STUB_CONFIRM ,	 
 // AUDIO_STUB_STOP_ID ,	 
	 
 /******************************************************************	 
 These ProcIDs are ACM_COMM related	 
 *******************************************************************/	 
 AUDIO_ACM_START_ID=100 , // ACM_COMM procID sarts from 100	 
 AUDIO_REGCPNT_ID , // 101	 
 AUDIO_REGCPNT_CONFIRM , // 102	 
	 
 AUDIO_ENABLEHWCPNT_ID , // 103	 
 AUDIO_ENABLEHWCPNT_CONFIRM , // 104	 
	 
 AUDIO_DISABLEHWCPNT_ID , // 105	 
 AUDIO_DISABLEHWCPNT_CONFIRM , // 106	 
	 
 AUDIO_SETCPNTVOL_ID , // 107	 
 AUDIO_SETCPNTVOL_CONFIRM , // 108	 
	 
 AUDIO_HWCPNTMUTE_ID , // 109	 
 AUDIO_HWCPNTMUTE_CONFIRM , // 110	 
	 
 AUDIO_STREAMINDICATE_ID , // 111 , From COMM to APPS	 
 AUDIO_STREAMRESPONSE , // 112 , From APPS to COMM	 
	 
 AUDIO_ENABLEOUTSTREAM_ID , // 113	 
 AUDIO_ENABLEOUTSTREAM_CONFIRM , // 114	 
	 
 AUDIO_DISABLEOUTSTREAM_ID , // 115	 
 AUDIO_DISABLEOUTSTREAM_CONFIRM , // 116	 
	 
 AUDIO_ENABLEINSTREAM_ID , // 117	 
 AUDIO_ENABLEINSTREAM_CONFIRM , // 118	 
	 
 AUDIO_DISABLEINSTREAM_ID , // 119	 
 AUDIO_DISABLEINSTREAM_CONFIRM , // 120	 
	 
 /* for enabling / disabling the audio at the begining / ending of a call */	 
 AUDIO_CONVERSATIONSTART_ID , // 121 , From COMM to APPS	 
 AUDIO_CONVERSATIONSTOP_ID , // 122 , From COMM to APPS	 
	 
 /*	 
 *Jackie , 2010 -0518	 
 * APPS audio send AUDIO_SETMSASETTING_ID to control MSA	 
 * COMM audio send AUDIO_GETMSASETTING_ID to APPS audio , APPS can refresh its audio calibration UI	 
 */	 
 AUDIO_SETMSASETTING_ID , // 123	 
 AUDIO_GETMSASETTING_ID , // 124	 
	 
 /*	 
 *Jackie , 2010 -0817	 
 * APPS audio send AUDIO_SYNC_CODEC_ID to sync gain information of codec chip	 
 */	 
 AUDIO_SYNC_CODEC_ID , // 125	 
	 
 /*	 
 *Jackie , 2010 -1207	 
 * MSA detect DTMF tone from far-end.	 
 */	 
 AUDIO_DTMFDETECT_ID , // 126 , From AP to CP: enable / disable	 
 AUDIO_DTMFDETECTED_ID , // 127 , From CP to AP:Forward detected DTMF code to AP audio	 
	 
 /*	 
 *Jackie , 2011 -0212	 
 * Speech logging feature	 
 */	 
 AUDIO_ENABLESPEECHLOGGING_ID , // 128 , From APPS to COMM: start speech logging	 
 AUDIO_DISABLESPEECHLOGGING_ID , // 129 , From APPS to COMM: stop speech logging	 
 AUDIO_TXSPEECHDATA_ID , // 130 , From COMM to APPS: tx speech data	 
 AUDIO_RXSPEECHDATA_ID , // 131 , From COMM to APPS: rx speech data	 
	 
 AUDIO_SETMSAGAIN_ID , // 132 , From APPS to COMM: Set MSA gain	 
 AUDIO_SETMSAGAIN_CONFIRM , // 133 , From COMM to APPS: Confirm	 
	 
 AUDIO_SETEQSETTING_ID , // 134 , From APPS to COMM: Set USER-EQ	 
 AUDIO_SETEQSETTING_CONFIRM , // 135 , From COMM to APPS: Confirm	 
	 
	 
 } ACM_EXTENT_ID;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_MSA_PCM = 0 , /* first format must be ' 0 ' - used by ' for ' loops */	 
 ACM_XSCALE_PCM ,	 
 ACM_I2S ,	 
 ACM_AUDIO_DATA , /* For DAI */	 
 ACM_AUX_FM ,	 
 ACM_AUX_HW_MIDI ,	 
 ACM_AUX_APP ,	 
	 
 /* Must be at the end */	 
 ACM_NO_FORMAT ,	 
 ACM_NUM_OF_AUDIO_FORMATS = ACM_NO_FORMAT ,	 
	 
	 
 ACM_AUDIO_FORMAT_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_AudioFormat;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 /* first device must be ' 0 ' - used by ' for ' loops */	 
 ACM_MAIN_SPEAKER = 0 // 0 , handset speaker	 
 , ACM_AUX_SPEAKER // 1 , handsfree speaker	 
 , ACM_HEADSET_SPEAKER // 2 , headset speaker	 
 , ACM_MONO_LEFT_SPEAKER // 3	 
 , ACM_MONO_RIGHT_SPEAKER // 4	 
 , ACM_BUZZER // 5	 
 , ACM_MIC // 6 , handset mic	 
 , ACM_MIC_DIFF // 7 ,	 
 , ACM_AUX_MIC // 8 , handsfree mic	 
 , ACM_AUX_MIC_DIFF // 9	 
 , ACM_BLUETOOTH_SPEAKER // 10 , bluetooth speaker	 
 , ACM_BLUETOOTH_MIC // 11 , bluetooth mic	 
 , ACM_DAI_OUT // 12	 
 , ACM_DAI_IN // 13	 
 , ACM_CAR_KIT_SPEAKER // 14	 
 , ACM_CAR_KIT_MIC // 15	 
 , ACM_INPUT_DEVICE_8 // 16	 
 , ACM_HEADSET_MIC // 17 , headset mic	 
 , ACM_MIC_EC // 18	 
 , ACM_AUX_MIC_EC // 19	 
 , ACM_HEADSET_MIC_EC // 20	 
 , ACM_MIC_LOOP_SPEAKER // 21	 
 , ACM_MIC_LOOP_EARPIECE // 22	 
 , ACM_HEADSET_MIC_LOOP // 23	 
	 
 , ACM_TTY_IN_45	 
 , ACM_INPUT_DEVICE_10 = ACM_TTY_IN_45 // 24	 
	 
 , ACM_TTY_IN_50	 
 , ACM_INPUT_DEVICE_11 = ACM_TTY_IN_50 // 25	 
	 
 , ACM_TTY_IN_HCO // 26	 
 , ACM_TTY_VCO_MIC // 27	 
 , ACM_TTY_VCO_MIC_DUALMIC // 28	 
 , ACM_INPUT_DEVICE_15 // 29	 
 , ACM_INPUT_DEVICE_16 // 30	 
 , ACM_INPUT_DEVICE_17 // 31	 
 , ACM_INPUT_DEVICE_18 // 32	 
 , ACM_INPUT_DEVICE_19 // 33	 
 , ACM_INPUT_DEVICE_20 // 34	 
 , ACM_INPUT_TEST_DEVICE = ACM_INPUT_DEVICE_20	 
 , ACM_INPUT_DEVICE_21 // 35	 
 , ACM_LINE_OUT = ACM_INPUT_DEVICE_21	 
	 
 , ACM_INPUT_DEVICE_22 // 36	 
 , ACM_INPUT_DEVICE_23 // 37	 
 , ACM_INPUT_DEVICE_24 // 38	 
 , ACM_INPUT_DEVICE_25 // 39	 
 , ACM_INPUT_DEVICE_26 // 40	 
 , ACM_INPUT_DEVICE_27 // 41	 
	 
 , ACM_TTY_OUT_45	 
 , ACM_OUTPUT_DEVICE_10 = ACM_TTY_OUT_45 // 42	 
	 
 , ACM_TTY_OUT_50	 
 , ACM_OUTPUT_DEVICE_11 = ACM_TTY_OUT_50 // 43	 
	 
 , ACM_TTY_HCO_SPEAKER // 44	 
 , ACM_TTY_OUT_VCO // 45	 
 , ACM_TTY_OUT_VCO_DUALMIC // 46	 
 , ACM_OUTPUT_DEVICE_15 // 47	 
 , ACM_OUTPUT_DEVICE_16 // 48	 
 , ACM_OUTPUT_DEVICE_17 // 49	 
 , ACM_OUTPUT_DEVICE_18 // 50	 
 , ACM_OUTPUT_DEVICE_19 // 51	 
 , ACM_OUTPUT_DEVICE_20 // 52	 
 , ACM_OUTPUT_TEST_DEVICE = ACM_OUTPUT_DEVICE_20	 
 , ACM_OUTPUT_DEVICE_21 // 53	 
 , ACM_OUTPUT_DEVICE_22 // 54	 
 , ACM_OUTPUT_DEVICE_23 // 55	 
 , ACM_OUTPUT_DEVICE_24 // 56	 
 , ACM_OUTPUT_DEVICE_25 // 57	 
 , ACM_OUTPUT_DEVICE_26 // 58	 
 , ACM_OUTPUT_DEVICE_27 // 59	 
 , ACM_OUTPUT_DEVICE_28 // 60	 
 , ACM_OUTPUT_DEVICE_29 // 61	 
	 
 , ACM_WB_BLUETOOTH_SPEAKER // 62 , WB BLUETOOTH speaker	 
 , ACM_WB_BLUETOOTH_MIC // 63 , WB BLUETOOTH mic	 
 , ACM_WB_BLUETOOTH_NREC_SPEAKER // 64 , WB BLUETOOTH NREC speaker	 
 , ACM_WB_BLUETOOTH_NREC_MIC // 65 , WB BLUETOOTH NREC mic	 
 , ACM_HEADPHONE_SPEAKER // 66 , HEADSET3POLE speaker	 
 , ACM_HEADPHONE_MIC // 67 , HEADSET3POLE mic	 
 , ACM_EXTRA_VOLUME_MAIN_SPEAKER // 68 , Handset speaker with extra volume on	 
 , ACM_EXTRA_VOLUME_MIC // 69 , Handset mic with extra volume on	 
 , ACM_EXTRA_VOLUME_AUX_SPEAKER // 70 , Aux speaker with extra volume on	 
 , ACM_EXTRA_VOLUME_AUX_MIC // 71 , Aux mic with extra volume on	 
 , ACM_BLUETOOTH6_SPEAKER // 72 , BLUETOOTH6 speaker	 
 , ACM_BLUETOOTH6_MIC // 73 , BLUETOOTH6 mic	 
 , ACM_BLUETOOTH7_SPEAKER // 74 , BLUETOOTH7 speaker	 
 , ACM_BLUETOOTH7_MIC // 75 , BLUETOOTH7 mic	 
 , ACM_BLUETOOTH8_SPEAKER // 76 , BLUETOOTH8 speaker	 
 , ACM_BLUETOOTH8_MIC // 77 , BLUETOOTH8 mic	 
 , ACM_BLUETOOTH_NREC_SPEAKER // 78 , BLUETOOTH-NREC speaker	 
 , ACM_BLUETOOTH_NREC_MIC // 79 , BLUETOOTH-NREC mic	 
	 
 // Jackie , 2011 -0222	 
 // Loop include codec and MSA	 
 , ACM_MAIN_SPEAKER__LOOP // 80 , handset speaker for loopback test	 
 , ACM_AUX_SPEAKER__LOOP // 81 , handsfree speaker for loopback test	 
 , ACM_HEADSET_SPEAKER__LOOP // 82 , headset speaker for loopback test	 
 , ACM_MIC__LOOP // 83 , handset mic for loopback test	 
 , ACM_AUX_MIC__LOOP // 84 , handsfree mic for loopback test	 
 , ACM_HEADSET_MIC__LOOP // 85 , headset mic for loopback test	 
 , ACM_HEADPHONE_SPEAKER__LOOP // 86 , bluetooth speaker for loopback test	 
 , ACM_HEADPHONE_MIC__LOOP // 87 , bluetooth mic for loopback test	 
	 
 // Jackie , 2011 -0603	 
 // Dual mic devices	 
 , ACM_MAIN_SPEAKER_DUALMIC // 88 , handset speaker for dual mic solution	 
 , ACM_AUX_SPEAKER_DUALMIC // 89 , handsfree speaker for dual mic solution	 
 , ACM_HEADSET_SPEAKER_DUALMIC // 90 , headset speaker for dual mic solution	 
 , ACM_BLUETOOTH_SPEAKER_DUALMIC // 91 , bluetooth speaker for dual mic solution	 
 , ACM_BLUETOOTH_NREC_SPEAKER_DUALMIC // 92 , bluetooth NREC speaker for dual mic solution	 
	 
 , ACM_MIC_DUALMIC // 93 , handset mic for dual mic solution	 
 , ACM_AUX_MIC_DUALMIC // 94 , handsfree mic for dual mic solution	 
 , ACM_HEADSET_MIC_DUALMIC // 95 , headset mic for dual mic solution	 
 , ACM_BLUETOOTH_MIC_DUALMIC // 96 , bluetooth mic for dual mic solution	 
 , ACM_BLUETOOTH_NREC_MIC_DUALMIC // 97 , bluetooth NREC mic for dual mic solution	 
	 
	 
 // Jackie , 2011 -0915	 
 // VT devices	 
 , ACM_MAIN_SPEAKER_VT // 98 , handset speaker for VT	 
 , ACM_AUX_SPEAKER_VT // 99 , handsfree speaker for VT	 
 , ACM_HEADSET_SPEAKER_VT // 100 , headset speaker for VT	 
 , ACM_BLUETOOTH_SPEAKER_VT // 101 , bluetooth speaker for VT	 
 , ACM_BLUETOOTH_NREC_SPEAKER_VT // 102 , bluetooth NREC speaker for VT	 
	 
 , ACM_MIC_VT // 103 , handset mic for VT	 
 , ACM_AUX_MIC_VT // 104 , handsfree mic for VT	 
 , ACM_HEADSET_MIC_VT // 105 , headset mic for VT	 
 , ACM_BLUETOOTH_MIC_VT // 106 , bluetooth mic for VT	 
 , ACM_BLUETOOTH_NREC_MIC_VT // 107 , bluetooth NREC mic for VT	 
	 
 // VT_DUALMIC devices	 
 , ACM_MAIN_SPEAKER_VT_DUALMIC // 108 , handset speaker for VT_DUALMIC	 
 , ACM_AUX_SPEAKER_VT_DUALMIC // 109 , handsfree speaker for VT_DUALMIC	 
 , ACM_HEADSET_SPEAKER_VT_DUALMIC // 110 , headset speaker for VT_DUALMIC	 
 , ACM_BLUETOOTH_SPEAKER_VT_DUALMIC // 111 , bluetooth speaker for VT_DUALMIC	 
 , ACM_BLUETOOTH_NREC_SPEAKER_VT_DUALMIC // 112 , bluetooth NREC speaker for VT_DUALMIC	 
	 
 , ACM_MIC_VT_DUALMIC // 113 , handset mic for VT_DUALMIC	 
 , ACM_AUX_MIC_VT_DUALMIC // 114 , handsfree mic for VT_DUALMIC	 
 , ACM_HEADSET_MIC_VT_DUALMIC // 115 , headset mic for VT_DUALMIC	 
 , ACM_BLUETOOTH_MIC_VT_DUALMIC // 116 , bluetooth mic for VT_DUALMIC	 
 , ACM_BLUETOOTH_NREC_MIC_VT_DUALMIC // 117 , bluetooth NREC mic for VT_DUALMIC	 
	 
 ////////////// Wu Bo , 2012 -0525 , support ' VOIP over modem ' ///////////////	 
 // VOIP devices	 
 , ACM_MAIN_SPEAKER_VOIP // 118 , handset speaker for VOIP	 
 , ACM_AUX_SPEAKER_VOIP // 119 , handfree speaker for VOIP	 
 , ACM_HEADSET_SPEAKER_VOIP // 120 , headset speaker for VOIP	 
 , ACM_BLUETOOTH_SPEAKER_VOIP // 121 , bluetooth speaker for VOIP	 
 , ACM_BLUETOOTH_NREC_SPEAKER_VOIP // 122 , bluetooth NREC speaker for VOIP	 
 , ACM_BLUETOOTH_SPEAKER_VOIP_WB // 123 , bluetooth speaker for VOIP WB	 
 , ACM_BLUETOOTH_NREC_SPEAKER_VOIP_WB // 124 , bluetooth NREC speaker for VOIP WB	 
	 
 , ACM_MIC_VOIP // 125 , handset mic for VOIP	 
 , ACM_AUX_MIC_VOIP // 126 , handfree mic for VOIP	 
 , ACM_HEADSET_MIC_VOIP // 127 , headset mic for VOIP	 
 , ACM_BLUETOOTH_MIC_VOIP // 128 , bluetooth mic for VOIP , NB	 
 , ACM_BLUETOOTH_NREC_MIC_VOIP // 129 , bluetooth NREC mic for VOIP , NB	 
 , ACM_BLUETOOTH_MIC_VOIP_WB // 130 , bluetooth mic for VOIP , WB	 
 , ACM_BLUETOOTH_NREC_MIC_VOIP_WB // 131 , bluetooth NREC mic for VOIP , WB	 
	 
 // VOIP_DUALMIC devices	 
 , ACM_MAIN_SPEAKER_VOIP_DUALMIC // 132 , handset speaker for VOIP_DUALMIC	 
 , ACM_AUX_SPEAKER_VOIP_DUALMIC // 133 , handfree speaker for VOIP_DUALMIC	 
 , ACM_HEADSET_SPEAKER_VOIP_DUALMIC // 134 , headset speaker for VOIP_DUALMIC	 
	 
 , ACM_MIC_VOIP_DUALMIC // 135 , handset mic for VOIP_DUALMIC ,	 
 , ACM_AUX_MIC_VOIP_DUALMIC // 136 , handfree mic for VOIP_DUALMIC ,	 
 , ACM_HEADSET_MIC_VOIP_DUALMIC // 137 , headset mic for VOIP_DUALMIC ,	 
	 
 , ACM_MAIN_SPEAKER__LOOP2 // 138 , handset speaker for loopback test for factory test	 
 , ACM_AUX_SPEAKER__LOOP2 // 139 , handsfree speaker for loopback test for factory test	 
 , ACM_HEADSET_SPEAKER__LOOP2 // 140 , headset speaker for loopback test for factory test	 
 , ACM_MIC__LOOP2 // 141 , handset mic for loopback test for factory test	 
 , ACM_AUX_MIC__LOOP2 // 142 , handsfree mic for loopback test for factory test	 
 , ACM_HEADSET_MIC__LOOP2 // 143 , headset mic for loopback test for factory test	 
 , ACM_HEADPHONE_SPEAKER__LOOP2 // 144 , bluetooth speaker for loopback test for factory test	 
 , ACM_HEADPHONE_MIC__LOOP2 // 145 , bluetooth mic for loopback test for factory test	 
	 
 /* Must be at the end */	 
 , ACM_NUM_OF_AUDIO_DEVICES	 
	 
 // Tag for search end of audio device table	 
 , ACM_NOT_CONNECTED = 0x7fffffff	 
	 
 , ACM_AUDIO_DEVICE_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_AudioDevice;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_FORMAT_NOT_SUPPORTED = 0 ,	 
 ACM_FORMAT_SUPPORTED = 1 ,	 
	 
 ACM_FORMAT_SUPPORTED_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_FormatSupported;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_PATH_IN = 0 , // Tx	 
 ACM_PATH_OUT = 1 , // Rx	 
	 
 /* Must be at the end */	 
 ACM_NUM_OF_PATHS ,	 
	 
 ACM_PATH_DIRECTION_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_PathDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 ACM_SCENARIO_AUDIO = 0 , // audio	 
 ACM_SCENARIO_VOICE = 1 , // voice	 
	 
 /* Must be at the end */	 
 ACM_SCENARIO_CNT ,	 
	 
 ACM_SCENARIO_ENUM_32_BIT = 0x7FFFFFFF // 32 bit enum compiling enforcement	 
 } ACM_SCENARIOT;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 unsigned short Configure ; // bit 0 :CP send confirmation to AP ; bit 1 : reuse speaker as receiver ; bit 2 : bypass PM813 PA	 
 unsigned short Always_Print_PCM ; // default:1 ( Print PCM in call ) ; If in production phase , set this to 0 to save traffic	 
 unsigned short Disable_All_Modules ; // default:0	 
	 
 unsigned char description [ 28 ] ;	 
 } ACM_Configuration;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 unsigned short shift ;	 
 unsigned short SSCR0_HIGH ;	 
 unsigned short SSCR0_LOW ;	 
 unsigned short SSCR1_HIGH ;	 
 unsigned short SSCR1_LOW ;	 
 unsigned short SSTSA_LOW ;	 
 unsigned short SSRSA_LOW ;	 
 unsigned short SSPSP_HIGH ;	 
 unsigned short SSPSP_LOW ;	 
	 
 // Tavor only:	 
 unsigned short SSACD_LOW ;	 
 unsigned short SSACDD_HIGH ;	 
 unsigned short SSACDD_LOW ;	 
 } GSSP_Configuration;

typedef void ( *ACM_ResetStatusInd ) ( void ) ;
typedef ACMAudioStreamOutStartRsp ACMAudioStreamInStartRsp ;
typedef ACMAudioStreamOutStartRsp ACMAudioStreamOutStopRsp ;
typedef ACMAudioStreamOutStartRsp ACMAudioStreamInStopRsp ;
//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_DATA_SET {	 
 unsigned long command ;	 
 unsigned long op ;	 
 unsigned long param1 ;	 
 unsigned char data [ ( 140 ) ] ;	 
 } ACIPC_AUDIO_VCM_ECALL_DATA_SET;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_DATA_GET {	 
 unsigned long command ;	 
 unsigned long op ;	 
 unsigned long param1 ;	 
 } ACIPC_AUDIO_VCM_ECALL_DATA_GET;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_VOICE_SET {	 
 unsigned long command ;	 
 unsigned long cmd_id ;	 
 unsigned long res_id ;	 
 unsigned long param2 ;	 
 } ACIPC_AUDIO_VCM_ECALL_VOICE_SET;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_VOICE_GET {	 
 unsigned long command ;	 
 unsigned long cmd_id ;	 
 unsigned long res_id ;	 
 } ACIPC_AUDIO_VCM_ECALL_VOICE_GET;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_DATA_IND {	 
 unsigned long command ;	 
 unsigned long urc_id ;	 
 unsigned long data ;	 
 } ACIPC_AUDIO_VCM_ECALL_DATA_IND;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_DATA_GET_CNF {	 
 unsigned long command ;	 
 unsigned long op ;	 
 unsigned long param1 ;	 
 unsigned long value1 ;	 
 unsigned long value2 ;	 
 } ACIPC_AUDIO_VCM_ECALL_DATA_GET_CNF;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_VOICE_IND {	 
 unsigned long command ;	 
 unsigned long res_id ;	 
 unsigned long res_state ;	 
 } ACIPC_AUDIO_VCM_ECALL_VOICE_IND;

//ICAT EXPORTED STRUCT 
 typedef struct _ACIPC_AUDIO_VCM_ECALL_VOICE_GET_CNF {	 
 unsigned long command ;	 
 unsigned long cmd_id ;	 
 unsigned long res_id ;	 
 unsigned long param2 ;	 
 } ACIPC_AUDIO_VCM_ECALL_VOICE_GET_CNF;

typedef void ( *AUDIO_ECALL_CNF_CB ) ( const ACIPC_AUDIO_VCM_ECALL_VOICE_GET_CNF* ecall_voice , const ACIPC_AUDIO_VCM_ECALL_DATA_GET_CNF* ecall_data ) ;
//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT8 data [ 256 ] ;	 
 } ACMAudioDSPSettings;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 UINT16 length ;	 
 UINT8 data [ 2048 ] ;	 
 } ACMAudioSpeechData;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 VC_HANDSET = 0 ,	 
 VC_HANDSFREE ,	 
 VC_HEADSET , // with mic	 
 VC_HEADPHONE , // without mic	 
 VC_BT ,	 
 VC_LOOPBACK ,	 
 VC_MAXCOUNT ,	 
	 
 AC_HANDSET = 64 ,	 
 AC_HANDSFREE ,	 
 AC_HEADSET , // with mic	 
 AC_HEADPHONE , // without mic	 
 AC_BT ,	 
 AC_KWS ,	 
	 
 AC_FM ,	 
 AC_MAXCOUNT ,	 
	 
 ACM_PROFILE_ID_ENUM_16_BIT = 0x7FFF // 16 bit enum compiling enforcement	 
 } ACM_PROFILE_ID;

typedef void ( *SetDownLinkStream ) ( DOWNLINKSTREAM_REQUEST *streamReq ) ;
typedef void ( *SetUpLinkStream ) ( const UINT8* buf , UINT32 size ) ;
typedef AmrPlaybackEventType AmrFileEventType ;
typedef void ( *AmrPlaybackEventCallback ) ( AmrPlaybackEventType , int ) ;
typedef AmrPlaybackConfigInfo AmrFileConfigInfo ;
typedef void ( *AmrStreamCallback ) ( const uint8_t* , uint32_t ) ;
typedef uint32_t AmrPlaybackHandle ;
typedef uint32_t AmrEncodeHandle ;
typedef uint32_t amrnb_enc_handle ;
typedef uint32_t amrwb_enc_handle ;
typedef uint32_t amrnb_dec_handle ;
typedef uint32_t amrwb_dec_handle ;
typedef uint32_t acm_audio_track_handle ;
typedef void ( *acm_audio_track_event_callback_t ) ( acm_audio_track_handle , acm_audio_track_event_t ) ;
typedef acm_audio_track_handle audio_track_handle ;
typedef uint32_t acm_audio_record_handle ;
typedef acm_audio_record_handle audio_record_handle ;
typedef void ( *acm_audio_record_event_callback_t ) ( acm_audio_record_handle , acm_audio_record_event_t ) ;
typedef void ( *AmrFrameCallback ) ( const uint8_t* , uint32_t ) ;
typedef void ( *AmrFrameRequest ) ( uint8_t* , uint32_t* ) ;
typedef uint32_t audio_effect_handle ;
typedef UINT8 FSMState ;
typedef UINT8 FSMEvent ;
typedef UINT8 FSMAction ;
typedef const UINT8* FSMStateTable ;
typedef FSMDescriptor* FSMPtr ;
typedef BOOL ( *FSMActionFunc ) ( FSMPtr fsm ) ;
typedef const FSMActionFunc* FSMActionFuncTable ;
typedef INT32 MSL_STATUS ;
typedef union _mslCallbackContext
 {
 MslDlSapStatusIndParms sapStatusIndParms ;
 MslDlCreateSapConfParms createSapConfParms ;
 MslDlDeleteSapConfParms deleteSapConfParms ;
 MslDlCeStatusIndParms ceStatusIndParms ;
 MslDlConnectIndParms connectIndParms ;
 MslDlConnectConfParms connectConfParms ;
 MslDlDisconnectIndParms disconnectIndParms ;
 MslDlDisconnectConfParms disconnectConfParms ;
 MslDlActivateIndParms activateIndParms ;
 MslDlActivateConfParms activateConfParms ;
 MslDlDmRxDataIndParms dmRxDataIndParms ;
 MslDlDmTxDataConfParms dmTxDataConfParms ;
 MslDlRxDataIndParms rxDataIndParms ;
 MslDlTxDataConfParms txDataConfParms ;

 MslClientDiscoverServiceConfParms discoverSvcConfParms ;
 MslClientAbortConfParms abortConfParms ;
 MslServerAddServiceConfParms addSvcConfParms ;
 } MslCallbackContext , *PMslCallbackContext ;
typedef MSL_STATUS ( *MSLDL_CTRL_CALLBACK ) (
 UINT32 ctrlCallbackPrimitive ,
 PMslCallbackContext ptParms
 ) ;
typedef MSL_STATUS ( *MSLDL_DATA_CALLBACK ) (
 UINT32 dataCallbackPrimitive ,
 PMslCallbackContext ptParms
 ) ;
typedef UINT8 Stbc_Status ;
typedef void ( *MslSalStbcStatusIndFunc ) ( UINT32 , Stbc_Status ) ;
typedef void ( *MslSalStbcCreateRpcPacketFunc ) ( UINT32 , void* , MslBuffer* ) ;
typedef void ( *MslSalStbcClientSvCallbackFunc ) ( UINT32 , UINT8* , UINT32 ) ;
typedef void ( *MslSalStbcServerSvCallbackFunc ) ( UINT32 , UINT8* , UINT32 , MslBuffer* ) ;
typedef void ( *MslSalStbcDataSendConfFunc ) ( UINT32 , Stbc_Status , void* ) ;
typedef void ( *MslSalStbcTimeoutReqFunc ) ( UINT32 ) ;
typedef Stbc_Status ( *MslSalStbcUnmarshalCallRespFunc ) ( UINT32 , UINT8* , UINT32 , void* ) ;
typedef UINT32 MSL_TRACE_LEVEL ;
typedef uint32_t AUDIO_FILE_ID ;
DIAG_FILTER ( AUDIO , AMR_DEC , amr_dec_continue , DIAG_INFORMATION)  
 diagStructPrintf ( " amr_dec_dump " , amr_dec_info [ i ] .pcm_buf , sz );

DIAG_FILTER ( AUDIO , AMR_DEC , amr_dec_event , DIAG_INFORMATION)  
 diagPrintf ( " flags:0x%lx " , event );

DIAG_FILTER ( AUDIO , AMR_DEC , openDecHandle , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx " , amr_dec_info [ i ] .magic );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStart , DIAG_INFORMATION)  
 diagPrintf ( " file_name:%s , rev:%s " , file_name , " 2.100000 .6 " );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStartFile_fail , DIAG_INFORMATION)  
 diagPrintf ( " file_name error! " );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStartStream , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx , rev:%s " , handle , " 2.100000 .6 " );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStartInfo , DIAG_INFORMATION)  
 diagStructPrintf ( " config_dump " , ( void* ) config , sizeof ( AmrPlaybackConfigInfo ) );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStop , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx , drain:%d " , handle , drain );

DIAG_FILTER ( AUDIO , AMR_DEC , amrGetPCMOutHandle , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx , track_handle:0x%lx " , handle , track_handle );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayStopWithName , DIAG_INFORMATION)  
 diagPrintf ( " file_name:%s , drain:%d " , file_name , drain );

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test1 
 int amr_dec_test1 ( void ) {	 
 int error_code = 0 ;	 
 AmrFileConfigInfo config = { 0 } ;	 
 error_code = amrPlayStart ( " test.amr " , &config , 0 ) ;	 
DIAG_FILTER ( AUDIO , AMR_DEC , amr_dec_test1 , DIAG_INFORMATION)  
 diagPrintf ( " %s " , error_code == 0 ? " success! " : " fail! " );

	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test2 
 int amr_dec_test2 ( int* p ) {	 
 AmrFileConfigInfo config = { 0 } ;	 
 config.option = *p ;	 
 amrPlayStart ( " test.amr " , &config , 0 ) ;	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test_latency 
 int amr_dec_test_latency ( int* p ) {	 
 AmrFileConfigInfo config = { 0 } ;	 
 AUDIO_PLAY_OPTION play_option = { 0 } ;	 
 play_option.latency2 = ( *p ) ;	 
 config.option = play_option.option ;	 
 amrPlayStart ( " test.amr " , &config , 0 ) ;	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test_farend 
 int amr_dec_test_farend ( void ) {	 
 int error_code = 0 ;	 
 AmrFileConfigInfo config = { 0 } ;	 
 AUDIO_PLAY_OPTION play_option = { 0 } ;	 
 play_option.dest_end = 0x1 ;	 
 config.option = play_option.option ;	 
 error_code = amrPlayStart ( " test.amr " , &config , 0 ) ;	 
DIAG_FILTER ( AUDIO , AMR_DEC , amr_dec_test_farend , DIAG_INFORMATION)  
 diagPrintf ( " %s " , error_code == 0 ? " success! " : " fail! " );

	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test_stop 
 int amr_dec_test_stop ( void ) {	 
 amrPlayStopWithName ( " test.amr " , 1 ) ;	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_test_stop_all 
 int amr_dec_test_stop_all ( void ) {	 
 amrStop ( ) ;	 
 return 0 ;	 
 }

DIAG_FILTER ( AUDIO , AMR_DEC , cleanupMsgQ , DIAG_INFORMATION)  
 diagPrintf ( " msgQ ref:0x%lx " , ref );

DIAG_FILTER ( AUDIO , AMR_DEC , amrPlayBuffer_dump , DIAG_INFORMATION)  
 diagStructPrintf ( " amr_stream_buffer " , ( void* ) data , size );

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_stream_test 
 int amr_dec_stream_test ( int* p ) {	 
 AmrPlaybackConfigInfo config = { 0 } ;	 
 config.option = *p ;	 
 config.block_size = 2 * 1024 ;	 
 return amrPlayStart ( " test.amr " , &config , 0 ) ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_dec_stream_test_stop 
 int amr_dec_stream_test_stop ( int* p ) {	 
 return amrPlayStop ( 0xffffffff , *p ) ;	 
 }

DIAG_FILTER ( AUDIO , AMR_ENC , pcm_dump , DIAG_INFORMATION)  
 diagStructPrintf ( " enc_source_dump " , pcm_data , pcm_size );

DIAG_FILTER ( AUDIO , AMR_ENC , amr_enc_continue_fail , DIAG_INFORMATION)  
 diagPrintf ( " can not write into file! " );

DIAG_FILTER ( AUDIO , AMR_ENC , amr_enc_event , DIAG_INFORMATION)  
 diagPrintf ( " flags:0x%lx " , event );

DIAG_FILTER ( AUDIO , AMR_ENC , openEncHandle , DIAG_INFORMATION)  
 diagPrintf ( " record mode:%d , handle:0x%lx " , amr_enc_info [ i ] .config.mode , amr_enc_info [ i ] .magic );

DIAG_FILTER ( AUDIO , AMR_ENC , amrEncStart , DIAG_INFORMATION)  
 diagPrintf ( " file_name:%s , handle:0x%lx , rev:%s " , file_name , handle , " 2.100000 .6 " );

DIAG_FILTER ( AUDIO , AMR_ENC , amrEncStartStream , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx , rev:%s " , handle , " 2.100000 .6 " );

DIAG_FILTER ( AUDIO , AMR_ENC , amrEncStopWithName , DIAG_INFORMATION)  
 diagPrintf ( " file_name:%s " , file_name );

DIAG_FILTER ( AUDIO , AMR_ENC , amrGetPCMInHandle , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx , record_handle:0x%lx " , handle , record_handle );

DIAG_FILTER ( AUDIO , AMR_ENC , amrEncStop , DIAG_INFORMATION)  
 diagPrintf ( " handle:0x%lx " , handle );

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_enc_test_start 
 int amr_enc_test_start ( void ) {	 
 int error_code = 0 ;	 
 AmrEncConfigInfo config = { 0 } ;	 
 config.mode = AUDIO_RECORD_MODE_TX ; // record tx pcm to amr	 
	 
 error_code = amrEncStart ( " test_enc.amr " , &config , 0 ) ;	 
DIAG_FILTER ( AUDIO , AMR_ENC , amr_enc_test_start , DIAG_INFORMATION)  
 diagPrintf ( " %s " , error_code == 0 ? " success! " : " fail! " );

	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_enc_test_stop 
 int amr_enc_test_stop ( void ) {	 
 amrEncStopWithName ( " test_enc.amr " ) ;	 
 return 0 ;	 
 }

DIAG_FILTER ( AUDIO , AMR_ENC , on_amr_frame_encoded , DIAG_INFORMATION)  
 diagStructPrintf ( " amr_frame_dump " , ( void* ) buf , size );

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_enc_test2_start 
 int amr_enc_test2_start ( void ) {	 
 AmrEncConfigInfo config = { 0 } ;	 
 config.rate = 5 ; // MR795	 
 config.mode = AUDIO_RECORD_MODE_TX ; // record tx pcm to amr	 
 config.callback = on_amr_frame_encoded ;	 
 amrEncStart ( 0 , &config , 0 ) ;	 
 return 0 ;	 
 }

//ICAT EXPORTED FUNCTION - Audio , AMR , amr_enc_test2_stop 
 int amr_enc_test2_stop ( void ) {	 
 amrEncStop ( 0xffffffff ) ;	 
 return 0 ;	 
 }

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbtk_amr.ppppp
//PPL Source File Name : \\mbtk\\hal\\amr\\mbtk_amr.cpp
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
typedef AmrPlaybackEventType AmrFileEventType ;
typedef void ( *AmrPlaybackEventCallback ) ( AmrPlaybackEventType , int ) ;
typedef AmrPlaybackConfigInfo AmrFileConfigInfo ;
typedef void ( *AmrStreamCallback ) ( const uint8_t* , uint32_t ) ;
typedef uint32_t AmrPlaybackHandle ;
typedef uint32_t AmrEncodeHandle ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\add.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\add.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\az_lsp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\az_lsp.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\bitno_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\bitno_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\bitreorder_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\bitreorder_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\bits2prm.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\bits2prm.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c2_9pf_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\c2_9pf_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\copy.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\copy.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
typedef unsigned int size_t ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\div_32.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\div_32.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\div_s.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\div_s.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\extract_h.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\extract_h.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\extract_l.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\extract_l.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\gains_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\gains_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\gc_pred.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\gc_pred.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\gmed_n.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\gmed_n.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\gray_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\gray_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\grid_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\grid_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\int_lpc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\int_lpc.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\inv_sqrt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\inv_sqrt.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\inv_sqrt_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\inv_sqrt_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_abs.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\l_abs.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_deposit_h.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\l_deposit_h.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_deposit_l.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\l_deposit_l.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_shr_r.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\l_shr_r.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\log2.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\log2.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\log2_norm.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\log2_norm.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\log2_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\log2_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsfwt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsfwt.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsp.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp_az.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsp_az.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp_lsf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsp_lsf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp_lsf_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsp_lsf_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\lsp_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mult_r.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\mult_r.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\negate.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\negate.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\norm_l.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\norm_l.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\norm_s.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\norm_s.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ph_disp_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\ph_disp_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pow2.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\pow2.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pow2_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\pow2_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pred_lt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\pred_lt.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_plsf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\q_plsf.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_plsf_3.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\q_plsf_3.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_plsf_3_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\q_plsf_3_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_plsf_5.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\q_plsf_5.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_plsf_5_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\q_plsf_5_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\qua_gain_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\qua_gain_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\reorder.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\reorder.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\residu.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\residu.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\round.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\round.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\set_zero.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\set_zero.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\shr.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\shr.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\shr_r.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\shr_r.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sqrt_l.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\sqrt_l.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sqrt_l_tbl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\sqrt_l_tbl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sub.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\sub.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\syn_filt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\syn_filt.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\vad1.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\vad1.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\weight_a.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\weight_a.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\window_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\common\\src\\window_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\a_refl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\a_refl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\agc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\agc.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\amrdecode.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\amrdecode.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\b_cn_cod.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\b_cn_cod.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\bgnscd.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\bgnscd.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c_g_aver.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\c_g_aver.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d_gain_c.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d_gain_c.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d_gain_p.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d_gain_p.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d_plsf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d_plsf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d_plsf_3.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d_plsf_3.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d_plsf_5.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d_plsf_5.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d1035pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d1035pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d2_11pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d2_11pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d2_9pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d2_9pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d3_14pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d3_14pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d4_17pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d4_17pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\d8_31pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\d8_31pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dec_amr.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dec_amr.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dec_gain.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dec_gain.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dec_input_format_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dec_input_format_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dec_lag3.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dec_lag3.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dec_lag6.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dec_lag6.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dtx_dec.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\dtx_dec.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ec_gains.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\ec_gains.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ex_ctrl.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\ex_ctrl.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\if2_to_ets.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\if2_to_ets.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\int_lsf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\int_lsf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lsp_avg.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\lsp_avg.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ph_disp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\ph_disp.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\post_pro.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\post_pro.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\preemph.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\preemph.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pstfilt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\pstfilt.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\qgain475_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\qgain475_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sp_dec.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\sp_dec.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wmf_to_ets.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\src\\wmf_to_ets.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\amrnb_dec_api.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\dec\\api\\amrnb_dec_api.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
typedef uint32_t amrnb_dec_handle ;
typedef uint32_t AUDIO_FILE_ID ;
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
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\amrencode.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\amrencode.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\autocorr.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\autocorr.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c1035pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c1035pf.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c2_11pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c2_11pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c2_9pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c2_9pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c3_14pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c3_14pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c4_17pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c4_17pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\c8_31pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\c8_31pf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\calc_cor.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\calc_cor.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\calc_en.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\calc_en.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cbsearch.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cbsearch.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cl_ltp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cl_ltp.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cod_amr.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cod_amr.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\convolve.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\convolve.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cor_h.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cor_h.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cor_h_x.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cor_h_x.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cor_h_x2.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\cor_h_x2.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\corrwght_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\corrwght_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dtx_enc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\dtx_enc.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\enc_lag3.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\enc_lag3.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\enc_lag6.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\enc_lag6.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\enc_output_format_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\enc_output_format_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ets_to_if2.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\ets_to_if2.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ets_to_wmf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\ets_to_wmf.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\g_adapt.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\g_adapt.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\g_code.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\g_code.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\g_pitch.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\g_pitch.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\gain_q.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\gain_q.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\hp_max.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\hp_max.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\inter_36.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\inter_36.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\inter_36_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\inter_36_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_comp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\l_comp.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_extract.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\l_extract.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\l_negate.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\l_negate.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lag_wind.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\lag_wind.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lag_wind_tab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\lag_wind_tab.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\levinson.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\levinson.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\lpc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\lpc.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ol_ltp.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\ol_ltp.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\p_ol_wgh.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\p_ol_wgh.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pitch_fr.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\pitch_fr.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pitch_ol.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\pitch_ol.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pre_big.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\pre_big.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pre_proc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\pre_proc.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\prm2bits.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\prm2bits.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_gain_c.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\q_gain_c.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\q_gain_p.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\q_gain_p.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\qgain475.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\qgain475.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\qgain795.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\qgain795.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\qua_gain.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\qua_gain.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\s10_8pf.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\s10_8pf.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\set_sign.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\set_sign.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sid_sync.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\sid_sync.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sp_enc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\sp_enc.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\spreproc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\spreproc.cpp
typedef unsigned int size_t ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\spstproc.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\spstproc.cpp
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ton_stab.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\src\\ton_stab.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\amrnb_enc_api.ppppp
//PPL Source File Name : \\mbtk\\amr\\amrnb\\enc\\api\\amrnb_enc_api.cpp
typedef unsigned int size_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef int8_t Word8 ;
typedef uint8_t UWord8 ;
typedef int16_t Word16 ;
typedef uint16_t UWord16 ;
typedef int32_t Word32 ;
typedef uint32_t UWord32 ;
typedef int32_t Flag ;
typedef uint32_t amrnb_enc_handle ;
typedef uint32_t AUDIO_FILE_ID ;
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
