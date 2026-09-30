#include "mbtk_comm_api.h"
#include "common.h"
#include "modules/memoryHandle.h"
void periodicTask(void *arg)
{
    (void)arg;
  ilmQueue_t ilmQueue = {0};
    uint32_t periodicCounter=0,FivesecComCounter=0;
    op_uart_printf("-1-periodicTask:my periodicTask start\r\n");
    while(1){
        ol_os_task_sleep(200);
        op_uart_printf("-1-periodicTask:my periodicCount=%lu\r\n",periodicCounter);
        periodicCounter++;
        FivesecComCounter++;
      if (periodicCounter >= (storedDatas.periodicTime)) {
        ilmQueue.dataSize = 1;
        ilmQueue.pktType = D_PERIODIC_INTERVAL;
        if (mainProcessQueue != NULL) {
          op_uart_printf("-1-periodicTask:periodic interval reached, sending D_PERIODIC_INTERVAL\r\n");
          ol_os_msgq_send(mainProcessQueue, sizeof(ilmQueue), &ilmQueue, MBTK_OS_NO_SUSPEND);
        }
        periodicCounter = 0;
      }

        if(FivesecComCounter>=D_FIVESEC_TIME){
         ilmQueue.dataSize = 1;
         ilmQueue.pktType = D_FIVESEC_COM;
         if (mainProcessQueue != NULL) {
           op_uart_printf("-1-periodicTask:five second interval reached, sending D_FIVESEC_COM\r\n");
           ol_os_msgq_send(mainProcessQueue, sizeof(ilmQueue), &ilmQueue, MBTK_OS_NO_SUSPEND);
         }
         FivesecComCounter=0;
        }


    }
    
    
}