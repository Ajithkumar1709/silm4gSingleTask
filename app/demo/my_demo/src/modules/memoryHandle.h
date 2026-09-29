#ifndef MEMORY_HANDLE_H
#define MEMORY_HANDLE_H

#include "../common.h"

void memoryHandle_firstBoot(void);
void memoryHandle_readConfigStoreWithBackup(void);
void memoryHandle_writeConfigStoreWithBackup(void);
configStore_t *memoryHandle_getConfigStore(void);
extern configStore_t configStore;
#endif // MEMORY_HANDLE_H
