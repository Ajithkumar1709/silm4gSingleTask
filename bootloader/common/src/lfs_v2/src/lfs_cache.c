/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                lfs_cache.c


GENERAL DESCRIPTION

    This file is for lfs cache operation.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2011 by Marvell, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who        what, where, why
--------   ------     ----------------------------------------------------------
11/26/08   zhoujin    Created module
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
//#include "osa.h"
#include "string.h"
//#include "utils.h"
#include "lfs_cache.h"
#include "lfs_api.h"
//#include "FlashPartition.h"
//#include "csw_mem.h"
//#include "osa_mem.h"
#include "loadTable.h"
#include "qspi_nor.h"
#include "bsp.h"


/*===========================================================================

            LOCAL MACRO
===========================================================================*/



/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/* LFS File Queue head. */
lfsMsgQ LfsFileQHdr[NUM_OF_PARTITION];

/* LFS message Queue head. */
lfsMsgQ LfsMsgQHdr[NUM_OF_PARTITION];

/* LFS semaphore Reference */
static OSSemaRef LfsSemaRef[NUM_OF_PARTITION];

/* LFS flag Reference*/
static OSAFlagRef LfsFlagRef = NULL;

/* LFS Cache task Reference*/
static OSTaskRef LfsTaskRef = NULL;

BOOL nvm_flash_type = FALSE;	//flash type 0:external,1:internal;

/*===========================================================================

            EXTERN DEFINITIONS AND DECLARATIONS FOR MODULE

===========================================================================*/

/* flash type: 0-external, 1-internal*/
extern BOOL nvm_flash_type;

/* dfs lfs */
extern dfs_lfs_t dfs_lfs[NUM_OF_PARTITION];

/* lfs flash infomation */
extern lfs_flash_info LfsFlashInfo[NUM_OF_PARTITION];

/*===========================================================================

                        EXTERN FUNCTION DECLARATIONS

===========================================================================*/

/***********************************************************************
 *
 * Name:        fdi_sem_lock
 *
 * Description: No Mutex in Nucleus so do Semaphore.
 *
 * Parameters:
 *  void
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
extern void fdi_sem_lock(void);

/***********************************************************************
 *
 * Name:        fdi_sem_unlock
 *
 * Description: No Mutex in Nucleus so do Semaphore.
 *
 * Parameters:
 *  void
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
extern void fdi_sem_unlock(void);

/*===========================================================================

                          INTERNAL FUNCTION DEFINITIONS

===========================================================================*/
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      GetLfsBlkInfo                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Get LFS Block info.                                 */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
lfsBlockInfo *GetLfsBlkInfo(int partition)
{
    return &(LfsFlashInfo[partition].lfsBlkInfo);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      GetLfsBlockMapInfo                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Get LFS Block Map infomation.                       */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
lfsBlkMapType *GetLfsBlockMapInfo(int partition)
{
    return &(LfsFlashInfo[partition].lfsBlkMap);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMsgQValid                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check the validity of LFS queque and return         */
/*      the status.                                                      */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      mvUsbNetQ                           usb net response queue       */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      TRUE                                Valid resonse queue          */
/*      FALSE                               Invalid resonse queue        */
/*                                                                       */
/*************************************************************************/
BOOL LfsMsgQValid(lfsMsgQ *queue)
{
    if (queue == NULL)
    {
        return FALSE;
    }

    if(queue->id != LFS_QUEQUE_ID)
    {
        LFS_ERROR("Invalid Q id 0x%x", queue->id);
        return FALSE;
    }

    if(queue->guard != LFS_QUEQUE_GUARD)
    {
        LFS_ERROR("Invalid Q guard 0x%x", queue->guard);
        return FALSE;
    }

    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMsgQInit                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function initializes lfs queue. It should be called         */
/*      on behalf of a queue prior to using the queue.                   */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      mvUsbNetQ                           Response head pointer        */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMsgQInit(lfsMsgQ *hdr)
{
    ASSERT(hdr != NULL);

    hdr->id     =   LFS_QUEQUE_ID;
    hdr->next   =   hdr;
    hdr->prev   =   hdr;
    hdr->cnt    =   0;
    hdr->guard  =   LFS_QUEQUE_GUARD;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMsgQPut                                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function places a data block at the tail of a lfs queue on  */
/*      behalf of a queue prior to using the queue.                      */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      hdr                                 The queue head pointer       */
/*      pRspQ                               The queue pointer            */
/*      len                                 the data length              */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMsgQPut(lfsMsgQ *hdr, lfsMsgQ *queue)
{
    UINT32 cpsr;

    ASSERT(LfsMsgQValid(hdr));

    queue->id           =   LFS_QUEQUE_ID;
    queue->guard        =   LFS_QUEQUE_GUARD;

    //cpsr = disableInterrupts();

    queue->next         =   hdr;
    queue->prev         =   hdr->prev;
    hdr->prev->next     =   queue;
    hdr->prev           =   queue;
    hdr->cnt++;

    //restoreInterrupts(cpsr);

    return;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMsgQGet                                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function removes the data block at head of a queue and      */
/*      returns a pointer to the data block. If the queue is empty, then */
/*      a NULL pointer is returned. queue on behalf of a queue prior to  */
/*      using the queue.                                                 */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      hdr                                 The queue head pointer       */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      pRspQ                               The returned queue pointer   */
/*                                                                       */
/*************************************************************************/
lfsMsgQ *LfsMsgQGet(lfsMsgQ *hdr)
{
    UINT32 cpsr;
    lfsMsgQ *pMsgQ = NULL;

    ASSERT(LfsMsgQValid(hdr));

    //cpsr = disableInterrupts();

    if(hdr->cnt > 0)
    {
        pMsgQ = hdr->next;
        ASSERT(LfsMsgQValid(pMsgQ));
        hdr->next = pMsgQ->next;
        pMsgQ->next->prev = hdr;
        hdr->cnt--;
    }

    //restoreInterrupts(cpsr);

    if(pMsgQ != NULL)
    {
        pMsgQ->next  = NULL;
        pMsgQ->prev  = NULL;
        pMsgQ->id    = LFS_QUNLINK_ID;
        pMsgQ->guard = LFS_QUNLINK_GUARD;
    }

    return pMsgQ;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMsgQRemove                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function removes the data block at head of a queue and      */
/*      returns a pointer to the data block. If the queue is empty, then */
/*      a NULL pointer is returned. queue on behalf of a queue prior to  */
/*      using the queue.                                                 */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      hdr                                 The queue head pointer       */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      pRspQ                               The returned queue pointer   */
/*                                                                       */
/*************************************************************************/
void LfsMsgQRemove(lfsMsgQ *hdr, lfsMsgQ *queue)
{
    UINT32 cpsr;

    ASSERT(LfsMsgQValid(hdr));

    //cpsr = disableInterrupts();

    if(hdr->cnt > 0)
    {
        queue->prev->next = queue->next;
        queue->next->prev = queue->prev;
        hdr->cnt--;
    }

    if(hdr->cnt == 0)
    {
        ASSERT(hdr->next == hdr);
    }

    //restoreInterrupts(cpsr);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsGetMsgQCnt                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function Get the LFS queque count.                          */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      mvUsbNetQ                           Response head pointer        */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
UINT32 LfsGetMsgQCnt(int partition)
{
    if (LfsFlashInfo[partition].useCache)
    {
        return LfsMsgQHdr[partition].cnt;
    }
    else
    {
        return 0;
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_cache_init                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize LFS cache.                               */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_cache_init(int partition)
{
    OSA_STATUS status;
    void *taskStack = NULL;
    lfsBlkMapType *pBlkMap = GetLfsBlockMapInfo(partition);
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

/*---------------------------------------------------------------------*/

    /* LFS block bit map initialize. */
    pBlkMap->LfsGrpCnt = ((pBlkProp->LfsEndBlock - pBlkProp->LfsStartBlock + 1) >> 0x05) + 1;

    LFSLogPrintf("LfsGrpCnt %d", pBlkMap->LfsGrpCnt);

    pBlkMap->LfsBlkTbl = malloc(pBlkMap->LfsGrpCnt * sizeof(UINT32));
    ASSERT(pBlkMap->LfsBlkTbl != NULL);

    memset((UINT8 *)pBlkMap->LfsBlkTbl, 0x00, pBlkMap->LfsGrpCnt * sizeof(UINT32));

    /* LFS file queue initialize. */
    LfsMsgQInit(&LfsFileQHdr[partition]);

    /* LFS cache task resource initialize. */
    if (LfsFlashInfo[partition].useCache)
    {
		#if 0
        /* LFS Mutex initialize. */
        LfsMutexInit(partition);

        /* LFS tx queue initialize. */
        LfsMsgQInit(&LfsMsgQHdr[partition]);

        /* LFS Flag initialize. */
        if (!LfsFlagRef)
        {
            status = OSAFlagCreate(&LfsFlagRef);
            ASSERT(status == OS_SUCCESS);
        }

        if (!LfsTaskRef)
        {
            /* LFS cahce task stack. */
            taskStack = malloc(LFS_TASK_STACK_SIZE);
            ASSERT(taskStack != NULL);

            /* LFS cache task initialize. */
            status = OSATaskCreate(&LfsTaskRef,
                                   taskStack,
                                   LFS_TASK_STACK_SIZE,
                                   LFS_TASK_PRIORITY,
                                   "LfsCach",
                                   lfs_cache_task,
                                   0);

            ASSERT(status == OS_SUCCESS);
        }
		#endif
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_write_back                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function set write back flag.                                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_write_back(int partition)
{
    if ((LfsFlashInfo[partition].useCache) && LfsFlagRef)
    {
        //OSAFlagSet(LfsFlagRef, 1<<partition, OSA_FLAG_OR);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_erase_all                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function erase all LFS flash region.                         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_erase_all(void)
{
    UINT32 size = 0, address = 0;

    /* calculate file system size. */
    size = get_nvm_end_address() - get_nvm_start_address();

    /* calculate nvm start address. */
    address = get_nvm_start_address() - CRANE_QSPI_BASE_ADDRESS;

    /* Erase file system. */
    mbtk_qspi_erase(address, size);

    LFSLogPrintf("lfs_erase_all address 0x%x, size 0x%x", address, size );
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_erase_partition                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function erase all LFS partition.                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_erase_partition(void)
{
    UINT32 ret = 0;
    UINT32 size = 0, address = 0;

    size = LFS_BLOCK_SIZE * 6;

    /* calculate nvm start address. */
    address = get_nvm_start_address() - CRANE_QSPI_BASE_ADDRESS;

    /* Erase file system. */
    ret = mbtk_qspi_erase(address, size);;
    ASSERT(ret == 0);

    LFSLogPrintf("lfs_erase_partition address 0x%x, size 0x%x", address, size );
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_erase_block                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function erase LFS block.                                    */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_erase_block(UINT32 block)
{
    UINT32 ret = 0, address = 0;

    /* calculate nvm start address. */
    address = get_nvm_start_address() - CRANE_QSPI_BASE_ADDRESS + LFS_BLOCK_SIZE * block;

    /* Erase file system. */
    ret = mbtk_qspi_erase(address, LFS_BLOCK_SIZE);
    ASSERT(ret == 0);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      Lfs_record_corrupted_files                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function record corrupted files and add it into file queue.  */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void Lfs_record_corrupted_files(lfs_t *lfs, lfs_mdir_t *dir, UINT16 id,
                int (*cb)(lfs_t *, lfs_mdir_t *, uint16_t, struct lfs_info *))
{
    UINT32 length = 0;
    lfsMsgQ *pFileQ = NULL;
    int i = 0, partition = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    struct lfs_info *info = NULL;
    lfs_flash_info *pInfo = (lfs_flash_info *)(lfs->cfg->context);

    /*---------------------------------------------------------------------*/

    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        pDfsLfs = &dfs_lfs[i];

        if (lfs == &pDfsLfs->lfs)
        {
            partition = i;
        }
    }

    if(pInfo->partition >= NUM_OF_PARTITION)
    {
        LFSLogPrintf("lfs: Ignore partition %d", pInfo->partition);
        return;
    }

    /* Calculate memory size. */
    length = sizeof(struct lfs_info) + sizeof(lfsMsgQ);

    /* Alloc memory for lfs info + lfsMsgQ. */
    pFileQ = (lfsMsgQ *)malloc(length);
    ASSERT(pFileQ != NULL);

    /* Memset allocated memory. */
    memset(pFileQ, 0x00, length);

    /* Set the LFS info pointer. */
    pFileQ->cache = (UINT8 *)((UINT32)pFileQ + sizeof(lfsMsgQ));

    /* Set the LFS info pointer. */
    info = (struct lfs_info *)pFileQ->cache;

    /* Get the LFS info of this ID. */
    cb(lfs, dir, id,  info);

    /* Record corrupted file info into queque. */
    LfsMsgQPut(&LfsFileQHdr[partition], pFileQ);

    return;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_remove_corrupted_files                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function precheck corrupted files and delete.                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_remove_corrupted_files(lfs_t *lfs)
{
    lfsMsgQ *pFileQ = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    struct lfs_info *info = NULL;
    int result = 0, i = 0, partition = 0;

    /*---------------------------------------------------------------------*/

    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        pDfsLfs = &dfs_lfs[i];

        if (lfs == &pDfsLfs->lfs)
        {
            partition = i;
        }
    }

    /* Find corrupted files and delete. */
    while((pFileQ = LfsMsgQGet(&LfsFileQHdr[partition])) != NULL)
    {
        info = (struct lfs_info *)(pFileQ->cache);
        result = lfs_remove(lfs, (const char *)info->name);
        LFSLogPrintf("lfs[PTN %d]: Remove Corrupted file %s, result %d", partition, (const char *)info->name, result);
        free(pFileQ);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_alloc_block_cache                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function alloc LFS cache memory.                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
lfsMsgQ * lfs_alloc_block_cache(UINT32 blocknum, int partition)
{
    lfsMsgQ *pMsgQ = NULL;
	#if 0
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    /*---------------------------------------------------------------------*/
    if(OsaGetPoolFreeRate() <= 20)
    {
        //RTI_LOG("Heap free %d", OsaGetPoolFreeRate());
        lfs_write_back_to_partition(FALSE, FALSE, partition);
    }

    pMsgQ = (lfsMsgQ *)malloc(pBlkProp->FlashBlockSize + sizeof(lfsMsgQ));
    ASSERT(pMsgQ != NULL);

    pMsgQ->cache = (UINT8 *)((UINT32)pMsgQ + sizeof(lfsMsgQ));
    pMsgQ->block = blocknum;
    pMsgQ->dirty = 0;

    LfsMsgQPut(&LfsMsgQHdr[partition], pMsgQ);
	#endif
    return pMsgQ;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_get_block_cache                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Go through all the entries and check if the block   */
/*      is cached or not. If cached, Return the cached buffer.           */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
lfsMsgQ * lfs_get_block_cache(UINT32 blocknum, int partition)
{
    UINT32 i = 0, cnt = LfsGetMsgQCnt(partition);
    lfsMsgQ *pMsgQ = NULL, *pHead = &LfsMsgQHdr[partition];

    /* Go through all the cache entries and check if the block number
    ** is cached or not.
    */
    for ( pMsgQ = pHead->prev; pMsgQ != pHead; pMsgQ = pMsgQ->prev)
    {
        if ( blocknum == pMsgQ->block )
        {
            ASSERT(LfsMsgQValid(pMsgQ));
            return pMsgQ;
        }

        ASSERT((i++) <= cnt);
    }

    return NULL;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_read_block_to_buf                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read the block data from flash to cached buffer.    */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
lfsMsgQ * lfs_read_block_to_buf(UINT32 blocknum, int partition)
{
    UINT32 flashaddress, ret;
    lfsMsgQ *pBlock = NULL, *pNewBlock = NULL;
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    /* Go through all the cache entries and check if the block number
    ** is cached or not.
    */
    pBlock = lfs_get_block_cache(blocknum, partition);

    /* Alloc new cache for LFS block  */
    pNewBlock = lfs_alloc_block_cache(blocknum, partition);
    ASSERT(pNewBlock != NULL);

    /* Memset new block cache  */
    memset(pNewBlock->cache, 0x00, pBlkProp->FlashBlockSize);

    /* If the block number is not cached, we should read block data
    ** from Flash to cache.
    */
    if(pBlock == NULL)
    {
        flashaddress = blocknum * pBlkProp->FlashBlockSize;

        ret = mbtk_qspi_read(flashaddress, (unsigned int )(pNewBlock->cache), pBlkProp->FlashBlockSize);
        ASSERT(ret == 0);

        FATSYS_TRACE("Read block %d from flash to cache", blocknum - pBlkProp->LfsStartBlock);
    }
    else
    {
        memcpy(pNewBlock->cache, pBlock->cache, pBlkProp->FlashBlockSize);

        FATSYS_TRACE("Read block %d to new cache", blocknum - pBlkProp->LfsStartBlock);
    }

    return pNewBlock;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_cache_read                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do cache read operation.                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL lfs_flash_cache_read(UINT32 flashaddress, UINT8 *Buf, UINT32 size, int partition)
{
    UINT8 *pt = NULL;
    lfsMsgQ *pBlock = NULL;
    UINT32 OffSet = 0, Length = 0;
    UINT32 ReadBlockNum = 0, ret = 0, address = 0;
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    ASSERT(Buf != NULL);

    /* Calculate the read block number and block offset.*/
    Length = size;
    ReadBlockNum = flashaddress / pBlkProp->FlashBlockSize;
    OffSet = flashaddress % pBlkProp->FlashBlockSize;

    /* Check whether flash address is in the range or not.*/
    if((ReadBlockNum < pBlkProp->LfsStartBlock)||
       (ReadBlockNum > pBlkProp->LfsEndBlock))
    {
        LFS_ERROR("%s: Flash address %x is out of range", __FUNCTION__, flashaddress);
        ASSERT(0);
    }

    /* Lock LFS mutex*/
    LfsCacheLock(partition);

    while (OffSet + Length >= pBlkProp->FlashBlockSize)
    {
        /* Go through all the map entries and check if the block number allocated memory
        or not. If allocated, Return the allocated buffer.
        */
        pBlock = lfs_get_block_cache(ReadBlockNum, partition);
        if(pBlock != NULL)
        {
            pt = (unsigned char *)(&(pBlock->cache[OffSet]));
            memcpy(Buf, pt, pBlkProp->FlashBlockSize- OffSet);
        }
        else
        {
            address = (pBlkProp->FlashBlockSize * ReadBlockNum) + OffSet;
            ret = mbtk_qspi_read(address, (unsigned int )Buf, (unsigned int)(pBlkProp->FlashBlockSize- OffSet));
            ASSERT(ret == 0);
        }

        Length -= (pBlkProp->FlashBlockSize - OffSet);
        Buf = Buf + pBlkProp->FlashBlockSize - OffSet;
        OffSet = 0;
        ReadBlockNum++;
    }

    if (Length != 0)
    {
        /* Go through all the map entries and check if the block number allocated memory
           or not. If allocated, Return the allocated buffer.
        */
        pBlock = lfs_get_block_cache(ReadBlockNum, partition);
        if(pBlock != NULL)
        {
            memcpy(Buf, &(pBlock->cache[OffSet]), Length);
        }
        else
        {
            address = (pBlkProp->FlashBlockSize * ReadBlockNum) + OffSet;
            ret = mbtk_qspi_read(address, (unsigned int )Buf, (unsigned int )Length);
            ASSERT(ret == 0);
        }
    }

    /* Unlock LFS mutex*/
    LfsCacheUnlock(partition);

    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_cache_write                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do cache write operation.                           */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL lfs_flash_cache_write(UINT32 flashaddress, UINT8 *Buf, UINT32 size, int partition)
{
    lfsMsgQ *pBlock = NULL;
    UINT32 OffSet = 0, Length = 0;
    UINT32 WriteBlockNum = 0;
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    ASSERT(Buf != NULL);

    /* Calculate the write block number and block offset.*/
    Length = size;
    WriteBlockNum = flashaddress / pBlkProp->FlashBlockSize;
    OffSet = flashaddress % pBlkProp->FlashBlockSize;

    /* Check whether flash address is in the range or not.*/
    if((WriteBlockNum < pBlkProp->LfsStartBlock)||
       (WriteBlockNum > pBlkProp->LfsEndBlock))
    {
        LFS_ERROR("%s: Flash address %x is out of range", __FUNCTION__, flashaddress);
        ASSERT(0);
    }

    /* Lock LFS mutex*/
    LfsCacheLock(partition);

    while ((OffSet + Length) >= pBlkProp->FlashBlockSize)
    {
        /* Go through all the map entries and check if the block number allocated memory
           or not. If allocated, Return the allocated buffer.
        */
        pBlock = lfs_read_block_to_buf(WriteBlockNum, partition);
        ASSERT(pBlock != NULL);

        memcpy(&(pBlock->cache[OffSet]), Buf, pBlkProp->FlashBlockSize - OffSet);
        pBlock->dirty = 0xFF;

        Length -= (pBlkProp->FlashBlockSize - OffSet);
        Buf = Buf + pBlkProp->FlashBlockSize - OffSet;
        OffSet = 0;
        WriteBlockNum++;
    }

    if (Length != 0)
    {
        /* Go through all the map entries and check if the block number allocated memory
           or not. If allocated, Return the allocated buffer.
        */
        pBlock = lfs_read_block_to_buf(WriteBlockNum, partition);
        ASSERT(pBlock != NULL);

        memcpy(&(pBlock->cache[OffSet]), Buf, Length);
        pBlock->dirty = 0xFF;
    }

    /* Unlock LFS mutex*/
    LfsCacheUnlock(partition);

    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_write_back_to_partition                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function write cached buffer back to partition.              */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL lfs_write_back_to_partition(BOOL lock, BOOL all, int partition)
{
#if 0
    BOOL erase = TRUE;
    UINT8 *pBuf = NULL;
    lfsMsgQ *pMsgQ = NULL;
    UINT32 block = 0, i = 0, lfs_blk = 0, flashaddress = 0, ret = 0;
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    if (!LfsFlashInfo[partition].useCache)
    {
        return TRUE;
    }

    while(LfsGetMsgQCnt(partition) > 0)
    {
        /* LFS mutex Lock */
        LfsMutexLock(lock, partition);

        /* Get data from LFS message Queue. */
        pMsgQ = LfsMsgQGet(&LfsMsgQHdr[partition]);
        if(!pMsgQ)
        {
            /* LFS mutex Unlock */
            LfsMutexUnlock(lock, partition);
            return TRUE;
        }

        if ( 0xFF == pMsgQ->dirty )
        {
            /* Get physical block number.*/
            block = pMsgQ->block;
            ASSERT((block >= pBlkProp->LfsStartBlock) && (block <= pBlkProp->LfsEndBlock));

            /* Get LFS block number.*/
            lfs_blk = block - pBlkProp->LfsStartBlock;

            /* Calculate Flash address.*/
            flashaddress = block * pBlkProp->FlashBlockSize;

            /* Check whether need to erase flash or not.*/
            if(!SysIsAssert())
            {
                pBuf = malloc(pBlkProp->FlashBlockSize);
                ASSERT(pBuf != NULL);

                ret = spi_nor_do_read(flashaddress, (unsigned int )pBuf, pBlkProp->FlashBlockSize, partition);
                ASSERT(ret == 0);

                erase = FALSE;

                for(i = 0; i < pBlkProp->FlashBlockSize; i += 4)
                {
                    if(((*((UINT32 *)(pBuf+i)))^0xFFFFFFFF) != 0)
                    {
                        erase = TRUE;
                        break;
                    }
                }

                free(pBuf);
            }
            else
            {
                erase = TRUE;
            }

            /* Erase the block before start to write.*/
            if(erase)
            {
                FATSYS_TRACE("[PTN %d] Erase block %d", partition, lfs_blk);
                ret = spi_nor_do_erase_4k(flashaddress, pBlkProp->FlashBlockSize, partition);
                ASSERT(ret == 0);
            }

            Lfs_set_block_flag(lfs_blk, FALSE, partition);

            /* Write the whole block to Flash.*/
            ret = spi_nor_do_write(flashaddress, (unsigned int)pMsgQ->cache, pBlkProp->FlashBlockSize, partition);
            ASSERT(ret == 0);
        }

        /* Free cache memory */
        free(pMsgQ);
        pMsgQ = NULL;

        /* LFS mutex Unlock */
        LfsMutexUnlock(lock, partition);

        /* Only flush one cache if not "all"*/
        if(!all)
        {
            break;
        }
    }
#endif
    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_write_back_to_flash                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function write cached buffer back to flash.                  */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL lfs_write_back_to_flash(BOOL lock, BOOL all)
{
    int i = 0;

    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        if (LfsFlashInfo[i].useCache)
        {
            lfs_write_back_to_partition(lock, all, i);
        }
    }

    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_cache_task                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The task write lfs cached buffer back to flash.                  */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_cache_task(void *argv)
{
    int i = 0;
    OSA_STATUS status;
    UINT32 flag_mask = 0, flag_value = 0;

    flag_mask = (1 << NUM_OF_PARTITION) - 1;

    FATSYS_TRACE("lfs: lfs_cache_task mask: 0x%x", flag_mask);

    while(1)
    {
        status = OSAFlagWait(LfsFlagRef, flag_mask, OSA_FLAG_OR_CLEAR, &flag_value, OSA_SUSPEND);
        ASSERT(status == OS_SUCCESS);

        for (i = 0; i < NUM_OF_PARTITION; i++)
        {
            if (flag_value & (1 << i))
            {
                lfs_write_back_to_partition(TRUE, TRUE, i);
            }
        }
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_cache_task_suspend                                           */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs cache task suspend operation.                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_cache_task_suspend(void)
{
    OSA_STATUS   OSAStatus;

    if(LfsTaskRef)
    {
        /* LFS cache Tasks Suspend */
        //OSAStatus = OSATaskSuspend(LfsTaskRef);
        //ASSERT(OSAStatus == OS_SUCCESS);
    }

}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_cache_task_resume                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs cache task resume operation.                 */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_cache_task_resume(void)
{
    OSA_STATUS   OSAStatus;

    if(LfsTaskRef)
    {
        /* LFS cache Tasks Suspend */
        //OSAStatus = OSATaskResume(LfsTaskRef);
        //ASSERT(OSAStatus == OS_SUCCESS);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      Lfs_set_block_flag                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function set/clear block erase flag.                         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void Lfs_set_block_flag(UINT32 block, BOOL alloc, int partition)
{
    UINT32 grp = 0, bit = 0;
    lfsBlkMapType *pBlkMap = GetLfsBlockMapInfo(partition);

    grp = block >> 0x05;
	bit = block & 0x1F;

    ASSERT(grp < pBlkMap->LfsGrpCnt);

    /* 1: No need to pre-erase */
    /* 0: Need to pre-erase */
    pBlkMap->LfsBlkTbl[grp] |= (0x01 << bit);

    if(alloc)
    {
        pBlkMap->Alloc = TRUE;
    }

    FATSYS_TRACE("[PTN %d][%s]block %d no need to pre-erase", partition, alloc ? "Alloc": "Clear", block);

#if 0
    else
    {
        /* Need to pre-erase */
        pBlkMap->LfsBlkTbl[grp] &= (~(0x01 << bit));
    }
#endif
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      Lfs_block_preerase_partition                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function pre-erase lfs block.                                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void Lfs_block_preerase_partition(int partition)
{
    BOOL erase = TRUE;
    UINT8 *pBuf = NULL;
    UINT32 i = 0, flashaddress = 0, ret = 0;
    UINT32 blk = 0, lfs_blk = 0, grp = 0, bit = 0;
    lfsBlkMapType *pBlkMap = GetLfsBlockMapInfo(partition);
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);

    if(!pBlkMap->Alloc || (!LfsFlashInfo[partition].useCache))
    {
        return;
    }

    /* Lock LFS mutex*/
    LfsMutexLock(TRUE, partition);

    /*Pre-Erase free block. */
    for(grp = pBlkMap->GrpOfst; grp < pBlkMap->LfsGrpCnt; grp++)
    {
        for(bit = pBlkMap->BitOfst; bit < 32; bit++)
        {
            /* Need to pre-erase */
            if(!(pBlkMap->LfsBlkTbl[grp] & (0x01 << bit)))
            {
                /* Clear pre-erase flag. */
                pBlkMap->LfsBlkTbl[grp] |= (0x01 << bit);

                /* Get LFS block number. */
                lfs_blk = (grp << 0x05) + bit;

                /* Get physical block number. */
                blk = lfs_blk + pBlkProp->LfsStartBlock;
                if(blk > pBlkProp->LfsEndBlock)
                {
                    continue;
                }

                /* Calculate Flash address.*/
                flashaddress = blk * pBlkProp->FlashBlockSize;

                /* Check whether need to erase flash or not.*/
                pBuf = malloc(pBlkProp->FlashBlockSize);
                ASSERT(pBuf != NULL);

                ret = mbtk_qspi_read(flashaddress, (unsigned int )pBuf, pBlkProp->FlashBlockSize);
                ASSERT(ret == 0);

                erase = FALSE;

                for(i = 0; i < pBlkProp->FlashBlockSize; i += 4)
                {
                    if(((*((UINT32 *)(pBuf+i)))^0xFFFFFFFF) != 0)
                    {
                        erase = TRUE;
                        break;
                    }
                }

                free(pBuf);

                /* Erase the block before start to write.*/
                if(erase)
                {
                    FATSYS_TRACE("PreErase block %d", lfs_blk);
                    ret = mbtk_qspi_erase(flashaddress, pBlkProp->FlashBlockSize);
                    ASSERT(ret == 0);

                    /* Update group and bit offset. */
                    bit++;
                    if(bit == 32)
                    {
                        bit = 0;

                        grp++;
                        if(grp == pBlkMap->LfsGrpCnt)
                        {
                            grp = 0;
                        }
                    }

                    pBlkMap->GrpOfst = grp;
                    pBlkMap->BitOfst = bit;

                    /* Unlock LFS mutex*/
                    LfsMutexUnlock(TRUE, partition);
                    return;
                }
                else
                {
                    FATSYS_TRACE("PreErase block %d, Already 0xFF", lfs_blk);
                }
            }
        }

        /* Reset bit offset. */
        pBlkMap->BitOfst = 0;

    }

    /* Reset group and bit offset. */
    pBlkMap->GrpOfst = 0;
    pBlkMap->BitOfst = 0;

    /* Unlock LFS mutex*/
    LfsMutexUnlock(TRUE, partition);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      Lfs_block_preerase                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function pre-erase lfs block.                                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void Lfs_block_preerase(void)
{
    int i = 0;

    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        if (LfsFlashInfo[i].useCache)
        {
            Lfs_block_preerase_partition(i);
        }
    }
}


/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMutexInit                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize lfs mutex.                               */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMutexInit(int partition)
{
    OSA_STATUS status;

    //status = OSASemaphoreCreate (&LfsSemaRef[partition], 1, OSA_FIFO);
    //ASSERT(status == OS_SUCCESS);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsCacheLock                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs cache lock.                                  */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsCacheLock(int partition)
{
    if (LfsSemaRef[partition])
    {
        OSA_STATUS status;

        //status = OSASemaphoreAcquire(LfsSemaRef[partition], OS_SUSPEND);
        //ASSERT(status == OS_SUCCESS);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsCacheUnlock                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs cache unlock.                                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsCacheUnlock(int partition)
{
    if (LfsSemaRef[partition])
    {
        OSA_STATUS status;

        //status = OSASemaphoreRelease(LfsSemaRef[partition]);
        //ASSERT(status == OS_SUCCESS);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMutexLock                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs mutex lock.                                  */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMutexLock(BOOL lock, int partition)
{
    if(lock)
    {
        /* Lock Fat system mutex*/
        //fdi_sem_lock();

        /* Lock LFS mutex*/
        LfsCacheLock(partition);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMutexUnlock                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs mutex unlock.                                */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMutexUnlock(BOOL lock, int partition)
{
    if(lock)
    {
        /* Unlock cache mutex*/
        LfsCacheUnlock(partition);

        /* UnLock Fat system mutex*/
        //fdi_sem_unlock();
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsMutexLockALL                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs mutex lock & FDI lock.                       */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void LfsMutexLockALL(void)
{
    int i = 0;

    /* Lock Fat system mutex*/
    //fdi_sem_lock();

    /* Lock LFS mutex*/
    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        LfsCacheLock(i);
    }
}

