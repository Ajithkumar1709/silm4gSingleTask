#ifndef __CORGET_API_H__
#define __CORGET_API_H__


#ifdef __cplusplus
extern "C" {
#endif

//#ifndef  __ASR_L501C_ZZD_CUSTOMER__ 
//#define  __ASR_L501C_ZZD_CUSTOMER__ 
//#endif


#if (defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_HAWK)|| defined(MBTK_POC_SUPPORT_CHAYU))

int OEM_init(void);

int OEM_SetRrcTime(int ticks);
/** Network*/
int OEMSocket_SetupUDP(unsigned char socket_id);
int OEMSocket_CloseUDP(unsigned char socket_id);
int OEMSocket_UdpReadData(unsigned char socket_id, char* data, unsigned short length);
int OEMSocket_SendUDP(unsigned char socket_id, char* ip, unsigned int port, char *buff, int length);
int OEMSocket_SetupTCP(unsigned char socket_id, char* ip, unsigned short port);
int OEMSocket_SendTCP(unsigned char socket_id,char * buffer,int buf_len);
int OEMSocket_ReadTcpData(unsigned char socket_id, const char* data, int length);
int OEMSocket_CloseTCP(unsigned char socket_id);
int OEMSocket_GetIpByName(char * name, char * ip);
int OEMSocket_Select(unsigned char socket_id, unsigned int timeout);

/** File */
int OEMFile_Open(const char *path, const char *oflag);
int OEMFile_Close(unsigned short filedes);
int OEMFile_Seek(unsigned short filedes,long offset, int where);
int OEMFile_Read(unsigned short filedes,void *buf,int size,int count);
int OEMFile_Write(unsigned short filedes,void *buf,int size,int count);

/* TTS */
int OEM_StarPlay(void);
int OEM_StopPlay(void);
int OEM_Play(const char *data, int length);
int OEM_GetPlayBufferAvail(void);
int OEM_CleanPlayBuffer(void);

/*unicode*/
int OEM_TTS_Spk( char* atxt);

//8k 16bit PCM 
int OEM_StarRecord(void);
int OEM_StopRecord(void);

/** Tone */

int OEM_PlayTone(int Type);

//printf log
void OEMLogPrintf(const char *fmt, ...);

/** Uart */
int OEM_SendUart(char *uf,int len); 

/** Timer ms*/
int OEM_SetTimer(unsigned int atime);
int OEM_CancelTimer(void);
/** System Timer */
unsigned long OEM_Get_time(void);
void OEMSleep(int ticks);

int OEM_SetCPUPerformance(int level);
int OEM_GetImeiInfo(char* imei);

/**User Msg Queue */  
int OEM_PostMessage(void* msg);
unsigned long OEM_PocGetMsgQueueRestSpace(void);
/***********************************************************************
 *
 * Name:        OEM_CreateTask
 *
 * Description: Create Task.
 *
 * Parameters:
 *  void                 	*taskRef      [OUT]    OS task reference
 *  void		                  	*stackPtr      [IN]    pointer to start of task stack area
 *  UINT32 	                  	stackSize      [IN]    number of bytes in task stack area
 *  UINT8                	    	priority     [IN]    task priority 0 - 252
 *  CHAR                 		*taskName      [IN]    task name
 *  void                 			*taskStart(void*)      [IN]   pointer to task entry point
 *  void                 			*argv      [IN]    task entry argument pointer
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
int OEM_CreateTask(
    void* taskRef,
    void*       stackPtr,
    unsigned int      stackSize,
    unsigned char       priority,
    char        *taskName,
    void        (*taskStart)(void*),
    void*       argv
 );
/*Semaphore*/
void OEM_SemaphoreCreate(void* SemaRef);
void OEM_SemaphoreAcquire(void* SemaRef);
void OEM_SemaphoreRelease(void* SemaRef);
/*Mutex*/
void OEM_MutexInit(void* MutexRef);
void OEM_MutexLock(void* MutexRef);
void OEM_MutexUnlock(void* MutexRef);


/*************************************************************************/
//lib interface
/*************************************************************************/
int  OEMSocket_RecvUDPDataCB(unsigned char socket_id);
int  OEMSocket_TCP_Connected(unsigned char socket_id);
int  OEMSocket_RecvTCPDataCB(unsigned char socket_id);
void OEM_Record(const char* data, int length);
void OEMPlayBufferAvailCB(int rest_data);
/* 1:TTS正在播放  0:TTS播放完毕 */
void OEM_TTS_Status_CB(int type);
void OEMPOC_AT_Recv(char* buf ,int len);
int  OEM_PendMessage(void* msg);
void OEMTimerOut(void);

/* 1 NET_CONNECTED 0 NET_DISCONNECTED */
void OEMNetworkStatusChange(int result);

//init
void OEM_PocInit(void);
void init_atpocnet(void);

#endif /*MBTK_POC_SUPPORT*/


#ifdef __cplusplus
}
#endif

#endif /*__CORGET_API_H__*/