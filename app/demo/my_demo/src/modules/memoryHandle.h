#ifndef MEMORY_HANDLE_H
#define MEMORY_HANDLE_H

#include "../common.h"

void memoryHandle_firstBoot(void);
void memoryHandle_readConfigStoreWithBackup(void);
void memoryHandle_writeConfigStoreWithBackup(void);
storedDatas_t *memoryHandle_getConfigStore(void);

/* Daily telemetry limit (storedDatas.maxPayload per IST day), counter kept in
 * storedDatas. Both are no-ops while NTP is not synced. */
U1 maxPayLoadChecker(void);   /* 1 = allowed to send, 0 = limit reached */
void maxPayLoadCount(void);   /* call after a telemetry publish succeeds */
extern storedDatas_t storedDatas;
#endif // MEMORY_HANDLE_H
