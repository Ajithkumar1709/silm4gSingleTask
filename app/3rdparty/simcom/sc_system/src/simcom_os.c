#include "simcom_os.h"
#include "mbtk_os.h"
#include "mbtk_err.h"

SC_STATUS sAPI_TaskCreate(sTaskRef *taskRef,
                               void* stackPtr,
                               UINT32 stackSize, 
                               UINT8 priority, 
                               char *taskName, 
                               void (*taskStart)(void*), 
                               void* argv)
{
    return ol_os_task_creat(taskRef, stackPtr, stackSize, priority, taskName, taskStart, argv);
}

SC_STATUS sAPI_TaskDelete(sTaskRef taskRef)
{
    return ol_os_task_delete(taskRef);
}

SC_STATUS sAPI_TaskSuspend(sTaskRef taskRef)
{
    return ol_os_task_suspend(taskRef);
}

SC_STATUS sAPI_TaskResume(sTaskRef taskRef)
{
    return ol_os_task_resume(taskRef);
}

void sAPI_TaskSleep(UINT32 ticks)
{
    return ol_os_task_sleep(ticks);
}

SC_STATUS sAPI_TaskGetCurrentRef(sTaskRef *taskRef)
{
    simcom_api_not_support();
    return SC_SUCCESS;
}

SC_STATUS sAPI_TaskTerminate(sTaskRef taskRef)
{
    simcom_api_not_support();
    return SC_SUCCESS;
}

SC_STATUS sAPI_MsgQCreate(sMsgQRef *msgQRef, 
                               char *queueName, 
                               UINT32 maxSize, 
                               UINT32 maxNumber, 
                               UINT32 waitingMode)
{
    return ol_os_msgq_creat(msgQRef, queueName, maxSize, maxNumber, waitingMode);
}

SC_STATUS sAPI_MsgQDelete(sMsgQRef msgQRef)
{
    return ol_os_msgq_delete(msgQRef);
}

SC_STATUS sAPI_MsgQSend(sMsgQRef msgQRef, SIM_MSG_T *msgPtr)
{
    return ol_os_msgq_send(msgQRef, sizeof(SIM_MSG_T), (char *)msgPtr, MBTK_OS_NO_SUSPEND);
}

SC_STATUS sAPI_MsgQRecv(sMsgQRef msgQRef,SIM_MSG_T *recvMsg, UINT32 timeout)
{
    return ol_os_msgq_recv(msgQRef, (char *)recvMsg, sizeof(SIM_MSG_T), timeout);
}

SC_STATUS sAPI_MsgQPoll(sMsgQRef msgQRef,UINT32* msgCount)
{
    return ol_os_msgq_poll(msgQRef, msgCount);
}

SC_STATUS sAPI_SemaphoreCreate(sSemaRef *semaRef, 
                                       UINT32 initialCount, 
                                       UINT32 waitingMode)
{
    return ol_os_sem_creat(semaRef, initialCount, waitingMode);
}

SC_STATUS sAPI_SemaphoreDelete(sSemaRef semaRef)
{
    return ol_os_sem_delete(semaRef);
}

SC_STATUS sAPI_SemaphoreAcquire(sSemaRef semaRef, UINT32 timeout)
{
    return ol_os_sem_request(semaRef, timeout);
}

SC_STATUS sAPI_SemaphoreRelease(sSemaRef semaRef)
{
    return ol_os_sem_release(semaRef);
}

SC_STATUS sAPI_SemaphorePoll(sSemaRef semaRef,UINT32 *count)
{
    return ol_os_sem_poll(semaRef, count);
}

SC_STATUS sAPI_MutexCreate(sMutexRef *mutexRef,UINT32 waitingMode)
{
    return ol_os_mutex_creat(mutexRef, waitingMode);
}

SC_STATUS sAPI_MutexDelete(sMutexRef mutexRef)
{
    return ol_os_mutex_delete(mutexRef);
}

SC_STATUS sAPI_MutexLock(sMutexRef mutexRef,UINT32 timeout)
{
    return ol_os_mutex_lock(mutexRef, timeout);
}

SC_STATUS sAPI_MutexUnLock(sMutexRef mutexRef)
{
    return ol_os_mutex_unlock(mutexRef);
}

SC_STATUS sAPI_FlagCreate(sFlagRef *flagRef)
{
    return ol_os_flag_creat(flagRef);
}

SC_STATUS sAPI_FlagDelete(sFlagRef flagRef)
{
    return ol_os_flag_delete(flagRef);
}

SC_STATUS sAPI_FlagSet(sFlagRef flagRef, UINT32 mask, UINT32 operation)
{
    return ol_os_flag_set(flagRef, mask, operation);
}

SC_STATUS sAPI_FlagWait(sFlagRef flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout)
{
    return ol_os_flag_wait(flagRef, mask, operation, flags, timeout);
}

SC_STATUS sAPI_TimerCreate(sTimerRef *timerRef)
{
    return ol_os_timer_creat(timerRef);
}

SC_STATUS sAPI_TimerStart(sTimerRef timerRef, UINT32 initialTime, UINT32 rescheduleTime, void (*callBackRoutine)(UINT32), UINT32 timerArgc)
{
    return ol_os_timer_start(timerRef, initialTime, rescheduleTime, callBackRoutine, timerArgc);
}

SC_STATUS sAPI_TimerStop(sTimerRef timerRef)
{
    return ol_os_timer_stop(timerRef);
}

SC_STATUS sAPI_TimerDelete(sTimerRef timerRef)
{
    return ol_os_timer_delete(timerRef);
}

UINT32 sAPI_GetTicks(void)
{
    return ol_os_get_ticks();
}

void sAPI_enableDUMP(void)
{
    simcom_api_not_support();
}


