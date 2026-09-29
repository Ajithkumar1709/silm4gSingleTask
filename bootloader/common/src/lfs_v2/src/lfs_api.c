/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                lfs_api.c


GENERAL DESCRIPTION

    This file is for LFS API.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2019 by ASR, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who        what, where, why
--------   ------     ----------------------------------------------------------
02/19/2019   zhoujin    Created module
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
//#include "FDI_EXT.h"
#include "FDI_FILE.h"
//#include "FDI_TYPE.h"
#include "lfs_api.h"
#include "lfs_trace.h"
#include "lfs_cache.h"
//#include "FlashPartition.h"
#include "FDI_Partition.h"
//#include "fat.h"
//#include "fatio.h"
//#include "fattypes.h"
#include "qspi_nor.h"
#include "utilities.h"
#include "loadTable.h"
#include "bsp.h"
//#include "osa.h"

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/* LFS trace flag */
BOOL LfsTraceEnable = FALSE;

/* dfs lfs */
dfs_lfs_t dfs_lfs[NUM_OF_PARTITION];

/* lfs flash infomation */
lfs_flash_info LfsFlashInfo[NUM_OF_PARTITION];

/* lfs file handle */
lfs_sHandle LfsFileDes[NUM_OF_PARTITION][LFS_NUM_HANDLES];

/* lfs mutex for partition*/
static OSASemaRef lfs_mutex[NUM_OF_PARTITION];

/* White list for LFS file system. */
const char lfs_white_list[][LFS_WHITE_LIST_LEN]=
{
    ".nvm",
    ".NVM",
    ".gki",
    ".GKI",
    ".csv",
    ".CSV",
    ".xml",
    ".dat"
};

/*===========================================================================

            EXTERN DECLARATIONS FOR MODULE

===========================================================================*/

/* LFS file numer. */
int FILE_NUM_LFS = 0;

/* Find file list. */
FILE_INFO FILE_LIST_LFS[MAX_NUM_OF_FILES];

/* FDI file system info */
extern FDI_file_system_info FDI_fsys_info[FDI_FSYS_MAX];

/*===========================================================================

            EXTERN DEFINITIONS AND DECLARATIONS FOR MODULE

===========================================================================*/

/*===========================================================================

                          INTERNAL FUNCTION DEFINITIONS

===========================================================================*/
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_get_partition                                                */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the file's partition number .                   */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static int lfs_get_partition(const char *filename)
{
    int i = 0, PrefixLen = 0;

/*---------------------------------------------------------------------*/

    if (strlen(filename) == 0)
    {
        return 0;
    }

    for (i = 0; i < FDI_FSYS_MAX; i++)
    {
        if (FDI_fsys_info[i].volume_label)
        {
            PrefixLen = strlen(FDI_fsys_info[i].volume_label);

            if((PrefixLen > 0) && (strlen(filename) >= PrefixLen) &&
                (memcmp((char *)filename, FDI_fsys_info[i].volume_label, PrefixLen) == 0))
            {
                return i;
            }
        }
    }

    return 0;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_get_prefixlen                                                */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the file name's prefix length.                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_get_prefixlen(const char *filename)
{
    int i = 0, PrefixLen = 0;

/*---------------------------------------------------------------------*/

    if (strlen(filename) == 0)
    {
        return 0;
    }

    for (i = 0; i < FDI_FSYS_MAX; i++)
    {
        if (FDI_fsys_info[i].volume_label)
        {
            PrefixLen = strlen(FDI_fsys_info[i].volume_label);

            if((PrefixLen > 0) && (strlen(filename)>= PrefixLen) &&
                (memcmp((char *)filename, FDI_fsys_info[i].volume_label, PrefixLen) == 0))
            {
                return PrefixLen;
            }
        }
    }

    return 0;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_get_prefix                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the prefix of file name.                        */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
const char *lfs_get_prefix(const char *filename)
{
    int i = 0, PrefixLen = 0;

/*---------------------------------------------------------------------*/

    for (i = 0; i < FDI_FSYS_MAX; i++)
    {
        if (FDI_fsys_info[i].volume_label)
        {
            PrefixLen = strlen(FDI_fsys_info[i].volume_label);

            if((PrefixLen > 0) && (strlen(filename)>= PrefixLen) &&
                (memcmp((char *)filename, FDI_fsys_info[i].volume_label, PrefixLen) == 0))
            {
                return (FDI_fsys_info[i].volume_label);
            }
        }
    }

    return (FDI_fsys_info[0].volume_label);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      LfsCacheLock                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs api lock.                                    */
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
static void lfs_lock(OSASemaRef sref)
{
    //OSASemaphoreAcquire(sref, OS_SUSPEND);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_unlock                                                       */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs api unlock.                                  */
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
static void lfs_unlock(OSASemaRef sref)
{
    //OSASemaphoreRelease(sref);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_read                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read a region in a block. The block must have       */
/*      previously been erased. Negative error codes are propogated to   */
/*      the user. May return LFS_ERR_CORRUPT if the block should be      */
/*      considered bad.                                                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static int lfs_flash_read(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, void* buffer, lfs_size_t size)
{
    lfs_flash_info *pInfo = NULL;
    UINT32 ret = 0, FlashAddrss = 0;

/*---------------------------------------------------------------------*/

    ASSERT(c != NULL);
    ASSERT(c->context != NULL);
    ASSERT(block < c->block_count);

    pInfo = (lfs_flash_info *)(c->context);

    FlashAddrss = (block * c->block_size) + pInfo->lfsBlkInfo.LfsStartAddress + off;

    if(pInfo->partition < NUM_OF_PARTITION)
    {
		
			#ifdef MBTK_EXTFS_INIT_BY_USER
			extern int mbtk_get_extfs_read_fun(unsigned int addr, unsigned int buf_addr, unsigned int size);
			if(pInfo->partition == PARTITION_1 && mbtk_get_extfs_read_fun(FlashAddrss, (unsigned int )buffer, size) != -100){
				return LFS_ERR_OK;
			}
			#endif
			
            if (pInfo->useCache)
            {
				#if 1
				lfs_flash_cache_read(FlashAddrss, (unsigned char *)buffer, (unsigned int)size, pInfo->flashIndex);
				#else
				lfs_flash_cache_read(FlashAddrss, (unsigned char *)buffer, (unsigned int)size, 0);
				#endif
            }
            else
            {
            	#if 1
				ret = mbtk_qspi_read(FlashAddrss, (unsigned int )buffer, (unsigned int)size);
				#else
                ret = spi_nor_do_read(FlashAddrss, (unsigned int )buffer, (unsigned int)size, 0);
				#endif
                ASSERT(ret == 0);
            }

    }else{
            ASSERT_EXT( FALSE, "Invalid partition %d", pInfo->partition);
    }

    return LFS_ERR_OK;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_prog                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Program a region in a block. The block must have    */
/*      previously been erased. Negative error codes are propogated to   */
/*      the user. May return LFS_ERR_CORRUPT if the block should be      */
/*      considered bad.                                                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static int lfs_flash_prog(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, const void* buffer, lfs_size_t size)
{
    lfs_flash_info *pInfo = NULL;
    UINT32 ret = 0, FlashAddrss = 0;

/*---------------------------------------------------------------------*/

    ASSERT(c != NULL);
    ASSERT(c->context != NULL);
    ASSERT(block < c->block_count);

    pInfo = (lfs_flash_info *)(c->context);

    FlashAddrss = (block * c->block_size) + pInfo->lfsBlkInfo.LfsStartAddress + off;

     if(pInfo->partition < NUM_OF_PARTITION)
     {
			#ifdef MBTK_EXTFS_INIT_BY_USER
			extern int mbtk_get_extfs_write_fun(unsigned int addr, unsigned int buf_addr, unsigned int size);
			if(mbtk_get_extfs_write_fun(FlashAddrss, (unsigned int )buffer, size) != -100){
				return LFS_ERR_OK;
			}
			#endif
		
            if (pInfo->useCache)
            {
            	#if 1
				lfs_flash_cache_write(FlashAddrss, (unsigned char *)buffer, (unsigned int)size, pInfo->flashIndex);
				#else
                lfs_flash_cache_write(FlashAddrss, (unsigned char *)buffer, (unsigned int)size, 0);
				#endif
            }
            else
            {
            	#if 1
				ret = mbtk_qspi_write(FlashAddrss, (unsigned int)buffer, (unsigned int)size);
				#else
                ret = spi_nor_do_write(FlashAddrss, (unsigned int)buffer, (unsigned int)size, 0);
				#endif
                ASSERT(ret == 0);
            }
    }else{
        ASSERT_EXT( FALSE, "Invalid partition %d", pInfo->partition);
    }

    return LFS_ERR_OK;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_erase                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Erase a block. A block must be erased before being  */
/*      programmed. The state of an erased block is undefined. Negative  */
/*      error codes are propogated to user. May return LFS_ERR_CORRUPT   */
/*      if the block should be considered bad.                           */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static int lfs_flash_erase(const struct lfs_config* c, lfs_block_t block)
{
    lfs_flash_info *pInfo = NULL;
    UINT32 ret = 0, FlashAddrss = 0;

    ASSERT(c != NULL);
    ASSERT(c->context != NULL);
    ASSERT(block < c->block_count);

/*---------------------------------------------------------------------*/

    pInfo = (lfs_flash_info *)(c->context);

    if (pInfo->useCache)
    {
        return LFS_ERR_OK;
    }

    //FATSYS_TRACE("%s[PTN %d]: block 0x%x", __FUNCTION__, pInfo->partition, block);

    FlashAddrss = (block * c->block_size) + pInfo->lfsBlkInfo.LfsStartAddress;

    if(pInfo->partition < NUM_OF_PARTITION)
    {

	
#ifdef MBTK_EXTFS_INIT_BY_USER
		extern int mbtk_get_extfs_earse_fun(unsigned int addr, unsigned int size);
		if(mbtk_get_extfs_earse_fun(FlashAddrss, block) != -100){
			return LFS_ERR_OK;
		}
#endif

            /* Erase the block .*/
		#if 1
			ret = mbtk_qspi_erase((unsigned int)FlashAddrss, (unsigned int)c->block_size);
		#else
            ret = spi_nor_do_erase_4k((unsigned int)FlashAddrss, (unsigned int)c->block_size, 0);
		#endif
            ASSERT(ret == 0);

     }else{
            ASSERT_EXT( FALSE, "Invalid partition %d", pInfo->partition);
    }

    return LFS_ERR_OK;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_flash_sync                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Sync the state of the underlying block device.       */
/*      Negative error codes are propogated to the user.                 */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static int lfs_flash_sync(const struct lfs_config* c)
{
    return LFS_ERR_OK;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_load_config                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function load LFS configuration                              */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_load_config(struct lfs_config* lfs_cfg, int partition)
{
    lfs_flash_info *pFlashInfo = &LfsFlashInfo[partition];
    lfsBlockInfo *pBlkProp = GetLfsBlkInfo(partition);
	unsigned int startAddrLfs = 0;
/*---------------------------------------------------------------------*/

    /* Initialize lfs information. */
    memset(pFlashInfo, 0x00, sizeof(lfs_flash_info));

    pFlashInfo->partition   = partition;
    pFlashInfo->useCache    = FALSE;

    switch (partition)
    {
		case PARTITION_0:
        {
			pBlkProp->LfsStartAddress   = get_nvm_start_address();
            pBlkProp->LfsEndAddress     = get_nvm_end_address() - 1;
#if 1
			startAddrLfs = get_nvm_start_address();
			pFlashInfo->flashIndex = mbtk_spi_check_type(&startAddrLfs);
#endif
		   break;
        }

#if (NUM_OF_PARTITION >= 2)
        case PARTITION_1:
        {
			pBlkProp->LfsStartAddress   = get_user_fs_start_address(); //0x0;
            pBlkProp->LfsEndAddress     = get_user_fs_end_address() - 1; //0x20000-1;
#if 1
			startAddrLfs = get_user_fs_start_address();
			pFlashInfo->flashIndex = mbtk_spi_check_type(&startAddrLfs);
#endif
            break;
        }
#endif

#if 1
		case PARTITION_2:
        {
			pBlkProp->LfsStartAddress   = get_user_nvm_begin_address(); //0x0;
            pBlkProp->LfsEndAddress     = get_user_nvm_end_address() - 1; //0x20000-1;
			startAddrLfs = get_user_nvm_begin_address();
			pFlashInfo->flashIndex = mbtk_spi_check_type(&startAddrLfs);
            break;
        }
		case PARTITION_3:
        {
			pBlkProp->LfsStartAddress   = get_user_fs2_begin_address(); //0x0;
            pBlkProp->LfsEndAddress     = get_user_fs2_end_address() - 1; //0x20000-1;
#if 1
			startAddrLfs = get_user_fs2_begin_address();
			pFlashInfo->flashIndex = mbtk_spi_check_type(&startAddrLfs);
#endif
            break;
        }
#endif

        default:
        {
            ASSERT(0);
            break;
        }
    }

    pBlkProp->FlashBlockSize    = LFS_BLOCK_SIZE;
    pBlkProp->LfsStartBlock     = pBlkProp->LfsStartAddress / pBlkProp->FlashBlockSize;
    pBlkProp->LfsEndBlock       = pBlkProp->LfsEndAddress / pBlkProp->FlashBlockSize;

    /* load lfs configuration. */
    lfs_cfg->context        = (void*)pFlashInfo;

    /* All partion use the same operations */
    lfs_cfg->read           = &lfs_flash_read;
    lfs_cfg->prog           = &lfs_flash_prog;
    lfs_cfg->erase          = &lfs_flash_erase;
    lfs_cfg->sync           = &lfs_flash_sync;
    lfs_cfg->read_size      = LFS_READ_SIZE;
    lfs_cfg->prog_size      = LFS_PROG_SIZE;
    lfs_cfg->block_size     = LFS_BLOCK_SIZE;
    lfs_cfg->cache_size     = LFS_CACHE_SIZE;
    lfs_cfg->name_max       = LFS_NAME_MAX;
    lfs_cfg->file_max       = LFS_FILE_MAX;
    lfs_cfg->attr_max       = LFS_ATTR_MAX;
    lfs_cfg->metadata_max   = lfs_cfg->block_size;
    lfs_cfg->block_cycles   = LFS_BLOCK_CYCLES;
    lfs_cfg->block_count    = pBlkProp->LfsEndBlock - pBlkProp->LfsStartBlock + 1;
    lfs_cfg->lookahead_size = LFS_ALIGN(lfs_cfg->block_count/8, 8);

    uart_printf("LfsAddress[PTN %d]: 0x%x ~ 0x%x, block: %d ~ %d, block cnt: %d, lookahead %d,buff %x",
           partition, pBlkProp->LfsStartAddress, pBlkProp->LfsEndAddress,
           pBlkProp->LfsStartBlock, pBlkProp->LfsEndBlock, lfs_cfg->block_count, lfs_cfg->lookahead_size,
           lfs_cfg->lookahead_buffer);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_root_is_valid                                                */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check whether root directory is valid or not.       */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_root_is_valid(const char *path)
{
    int handle = 0, result = 0;

/*---------------------------------------------------------------------*/

    handle = lfs_io_dir_open(path);
    if(handle < 0)
    {
        LFSLogPrintf("lfs: Fail to open root dir, status %d", handle);
        return LFS_ERR_BADF;
    }

    result = lfs_io_dir_close(handle);
    if(result != LFS_ERR_OK)
    {
        LFSLogPrintf("lfs: Fail to close root dir, status %d", result);
        return result;
    }

    result = lfs_sys_traverse(path);
    if (result != LFS_ERR_OK)
    {
        LFSLogPrintf("lfs: Fail to traverse lfs system, status %d", result);
        return result;
    }

    LFSLogPrintf("lfs root is valid");

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_GetTraceMode                                                 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get LFS trace mode                                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_get_trace_mode(void)
{
    //if(rti_get_mode() == rti_fsyslog_mode)
    //{
    //    LfsTraceEnable = TRUE;
    //}
    //else
    //{
    //    LfsTraceEnable = FALSE;
    //}
    LfsTraceEnable = TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_sys_init                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize LFS system                               */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_sys_init(void)
{
    int i = 0;
    OSA_STATUS status;

/*---------------------------------------------------------------------*/

    /* LFS get trace flag. */
    lfs_get_trace_mode();

    /* lfs partition init. */
	if(get_nvm_bin_size()!=0)
    	lfs_partition_init(PARTITION_0);

    /* lfs partition 1 init. */
	if(get_user_fs_exist())
    	lfs_partition_init(PARTITION_1);

#if 1
	if(get_user_nvm_exist()!=0)
    	lfs_partition_init(PARTITION_2);
	
	if(get_user_fs2_exist()!=0)
    	lfs_partition_init(PARTITION_3);
#endif

    return 0;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_check_system_space                                           */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check file system free space.                       */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
static void lfs_check_system_space(const char *volume_label)
{
    BOOL Delete = FALSE;
    UINT32 free_size = 0;
    char *filename = NULL;
    lfs_size_t in_use = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    int i = 0, j = 0, partition = 0, result = 0;

/*---------------------------------------------------------------------*/

    partition = lfs_get_partition(volume_label);

    pDfsLfs = &dfs_lfs[partition];

    /* Get total sectors and free sectors */
    in_use = lfs_fs_size(&(pDfsLfs->lfs));

    /* Calculate free size */
    free_size = (pDfsLfs->lfs.cfg->block_count - in_use) * pDfsLfs->lfs.cfg->block_size;

    LFSLogPrintf("[PTN %d] free size: %lu", partition, free_size);

    if(free_size != 0)
    {
        return;
    }
#if 0
    /* We should delete non-system files to free space. */
    lfs_io_findall(volume_label);

    for (i = 0; (i < FILE_NUM_LFS) && (i < MAX_NUM_OF_FILES); i ++)
	{
	    filename = FILE_LIST_LFS[i].file_name;

	    Delete = TRUE;

    	for(j = 0; j < sizeof(lfs_white_list)/LFS_WHITE_LIST_LEN; j++)
    	{
    		if(strstr(filename, lfs_white_list[j]) != NULL)
    		{
    			Delete = FALSE;
    			break;
    		}
    	}

        if(Delete)
        {
            result = lfs_remove(&(pDfsLfs->lfs), filename);
            LFSLogPrintf("Remove %s, result %d",  filename, result);
        }
	}
#endif
}


/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_partition_init                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize LFS system in partition                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_partition_init(int partition)
{
    int err = 0;
    lfs_file_t file;
    FDI_Fsys_Type fsys = FDI_FSYS_LFS_0;
    dfs_lfs_t *pDfsLfs = NULL;
#if 1//def MBTK_EXTFS_INIT_BY_USER
char *volume;
#endif

/*---------------------------------------------------------------------*/

    if (partition >= NUM_OF_PARTITION)
    {
        uart_printf("Invalid LFS PTN %d", partition);
        return -1;
    }

    switch(partition)
    {
        case PARTITION_0:
        {
            /* Register lfs partition 0 into FDI file system info. */
            fsys = FDI_FSYS_LFS_0;
            FDI_Transport_Fsys_Register(FDI_FSYS_LFS_0, FDI_C_VOLUME);
            break;
        }

#if (NUM_OF_PARTITION >= 2)
        case PARTITION_1:
        {
            /* Register lfs partition 1 into FDI file system info. */
		
#ifndef MBTK_EXTFS_INIT_BY_USER
				volume = FDI_D_VOLUME;
#else
				extern char *mbtk_get_extfs_sym(void);
				volume = (strlen(mbtk_get_extfs_sym())==NULL) ? FDI_D_VOLUME : mbtk_get_extfs_sym();
#endif
            fsys = FDI_FSYS_LFS_1;
            FDI_Transport_Fsys_Register(FDI_FSYS_LFS_1, volume);
            break;
        }
#endif

#if 1
	   case PARTITION_2:
	   	{
            /* Register lfs partition 1 into FDI file system info. */
		    fsys = FDI_FSYS_LFS_2;
            FDI_Transport_Fsys_Register(FDI_FSYS_LFS_2, FDI_E_VOLUME);
            break;
        }	
	   case PARTITION_3:
	   	{
            /* Register lfs partition 1 into FDI file system info. */
		    fsys = FDI_FSYS_LFS_3;
            FDI_Transport_Fsys_Register(FDI_FSYS_LFS_3, FDI_F_VOLUME);
            break;
        }
#endif

        default:
        {
            ASSERT(0);
            break;
        }
    }

    pDfsLfs = &dfs_lfs[partition];

    /* Initialize lfs database. */
    memset(pDfsLfs, 0x00, sizeof(dfs_lfs_t));

    /* Load LFS configuration. */
    lfs_load_config(&(pDfsLfs->cfg), partition);

    /* LFS cache initialize. */
    lfs_cache_init(partition);

    /* mount the filesystem */
    err = lfs_mount(&(pDfsLfs->lfs), &(pDfsLfs->cfg));

    /* Check root directory validity */
    if (!err)
    {
        err = lfs_root_is_valid(FDI_fsys_info[fsys].volume_label);
    }

    /* Reformat if we can't mount the filesystem
     * this should only happen on the first boot
    */
    if (err)
    {
        LFS_ERROR("Fail to mount in PTN %d, err %d", partition, err);
        lfs_format(&(pDfsLfs->lfs), &(pDfsLfs->cfg));
        lfs_mount(&(pDfsLfs->lfs), &(pDfsLfs->cfg));
    }

    /* Check system space */
    lfs_check_system_space(FDI_fsys_info[fsys].volume_label);

    uart_printf("lfs[PTN %d] init success", partition);

    return 0;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_get_freehandle                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Find the next free handle.                          */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_get_freehandle(int partition)
{
    int Handle = 0;

/*---------------------------------------------------------------------*/

    for (Handle = 0; Handle < LFS_NUM_HANDLES; ++Handle)
    {
        if (LfsFileDes[partition][Handle].oflag == LFS_FREE_HANDLE)
        {
            return Handle;
        }
    }

    LFSLogPrintf("lfs[PTN %d]: No free handle", partition);

    return LFS_BAD_HANDLE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_valid_handle                                                 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check whether lfs handle is valid or not.           */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_valid_handle(int Handle, int partition)
{
    if (partition < 0 || partition >= NUM_OF_PARTITION)
    {
        LFSLogPrintf("%s: invalid partition: %d", __FUNCTION__, partition);
        return -1;
    }

    Handle = INT_PARTITION_HANDLE(Handle, partition);

    if (Handle < 0 || Handle >= LFS_NUM_HANDLES)
    {
        LFSLogPrintf("%s: Handle: %d, partition: %d", __FUNCTION__, Handle, partition);
        return -1;
    }

    if (LfsFileDes[partition][Handle].oflag == LFS_FREE_HANDLE)
    {
        LFSLogPrintf("%s: %d is free handle", __FUNCTION__, Handle);
        return -1;
    }

    lfs_check_handle_validity(LfsFileDes, partition, Handle);

    return Handle;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_file_verify                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function verify file validity                                */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL lfs_file_verify(int Handle, BOOL set, int partition)
{
    int soff = 0;
    UINT8 *buf = NULL;
    char *pName = NULL;
    int i = 0, size = 0, fsize = 0, nsize = 0;
    UINT16 cksum = 0, orisum = 0, checkwidth = 1;
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = &dfs_lfs[partition];

/*---------------------------------------------------------------------*/

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    if(LfsFileDes[partition][Handle].CkSum != LFS_CKSUM_ID)
    {
        return TRUE;
    }

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    /* Get the file size. */
    fsize = lfs_file_size(&(pDfsLfs->lfs), file);
    if(fsize == 0)
    {
        return TRUE;
    }

    if(fsize > (LFS_BLOCK_SIZE*3))
    {
        LFSLogPrintf("lfs: fsize %d exceed check range", fsize);
        return TRUE;
    }

    /* Seek start position. */
    soff = lfs_file_seek(&(pDfsLfs->lfs), file, 0, LFS_SEEK_SET);
    if (soff < 0)
    {
        LFSLogPrintf("%s: lfs_file_seek soff %d", __FUNCTION__, soff);
        return FALSE;
    }

    buf = (UINT8 *)malloc(fsize);
    if(!buf)
    {
        return TRUE;
    }

    size = lfs_file_read(&(pDfsLfs->lfs), file, buf, fsize);
    if (size != fsize)
    {
        free(buf);
        LFSLogPrintf("%s: read size %d %d", __FUNCTION__, size, fsize);
        return FALSE;
    }

    checkwidth = 1;

    cksum = buf[0]<<8;

    for(i = 1; i < fsize - 1 ; i = i + checkwidth)
    {
        cksum ^= buf[i];
    }

    pName = LfsFileDes[partition][Handle].Name;

    nsize = strlen(pName);

    ASSERT(nsize <= LFS_NAME_MAX);

    for(i = 0; i < nsize; i = i++)
    {
        cksum ^= pName[i];
    }

    cksum += (buf[fsize-1]<<8);

    if(set)
    {
        //lfs_setattr(&(pDfsLfs->lfs), pName, LFS_CKSM_ATTR, &cksum, sizeof(UINT16));
        memcpy(file->cfg->attrs->buffer, &cksum, sizeof(UINT16));
    }
    else
    {
        //lfs_getattr(&(pDfsLfs->lfs), pName, LFS_CKSM_ATTR, &orisum, sizeof(UINT16));
        memcpy(&orisum, file->cfg->attrs->buffer, sizeof(UINT16));

        FATSYS_TRACE("origin/file checksum 0x%x 0x%x", cksum, orisum);

        if(cksum != orisum)
        {
            free(buf);
            LFSLogPrintf("lfs: Mismatch checksum 0x%x 0x%x", cksum, orisum);
            return FALSE;
        }

        /* Seek back to start position. */
        soff = lfs_file_seek(&(pDfsLfs->lfs), file, 0, LFS_SEEK_SET);
        if (soff < 0)
        {
            free(buf);
            LFSLogPrintf("%s: lfs_file_seek soff %d", __FUNCTION__, soff);
            return FALSE;
        }
    }

    FATSYS_TRACE("%s: file size %d", __FUNCTION__, fsize);

    free(buf);
    return TRUE;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_init_file_cfg                                                */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize lfs file configuration.                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
struct lfs_file_config * lfs_init_file_cfg(void)
{
    struct lfs_file_config *cfg = NULL;
    UINT32 length = sizeof(struct lfs_file_config) + sizeof(struct lfs_attr) + sizeof(UINT16);

/*---------------------------------------------------------------------*/

    cfg = (struct lfs_file_config *)malloc(length);
    memset(cfg, 0x00, sizeof(length));

    cfg->attr_count     = 1;
    cfg->attrs          = (struct lfs_attr *)((UINT32)cfg + sizeof(struct lfs_file_config));
    cfg->attrs->type    = LFS_CKSM_ATTR;
    cfg->attrs->size    = sizeof(UINT16);
    cfg->attrs->buffer  = (UINT8 *)((UINT32)cfg + sizeof(struct lfs_file_config) + sizeof(struct lfs_attr));

    return cfg;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_file_handle_cleanup                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function clean up lfs file handle resource.                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_file_handle_cleanup(int partition, int Handle)
{

/*---------------------------------------------------------------------*/

    if(LfsFileDes[partition][Handle].Name != NULL)
    {
        free(LfsFileDes[partition][Handle].Name);
    }

    if(LfsFileDes[partition][Handle].u.LfsFd.file.cfg != NULL)
    {
        free((void *)LfsFileDes[partition][Handle].u.LfsFd.file.cfg);
    }

    memset(&LfsFileDes[partition][Handle], 0x00, sizeof(lfs_sHandle));
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_open                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Open or create a file for read/write.               */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_open(CONST char *filename, UINT32 oflag, UINT32 pmode)
{
    BOOL NeedCheck = FALSE;
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    UINT32 filenameLen = 0;
    struct lfs_file_config *cfg = NULL;
    int i = 0, result = 0, flags = 0, Handle = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s: %s", __FUNCTION__, filename);

    partition = lfs_get_partition(filename);

    filename += lfs_get_prefixlen(filename);

    filenameLen = strlen(filename);
    if(filenameLen > LFS_NAME_MAX)
    {
        LFSLogPrintf("lfs: file name length %lu exceed %lu", filenameLen, LFS_NAME_MAX);
        return LFS_ERR_NAMETOOLONG;
    }

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    lfs_remove_corrupted_files(&(pDfsLfs->lfs));

    Handle = lfs_get_freehandle(partition);
    if(Handle < 0)
    {
        lfs_unlock(lfs_mutex[partition]);
        return Handle;
    }

    if (oflag & fatIO_RDONLY)
    {
        flags |= LFS_O_RDONLY;
    }

    if (oflag & fatIO_WRONLY)
    {
        flags |= LFS_O_WRONLY;
    }

    if (oflag & fatIO_RDWR)
    {
        flags |= LFS_O_RDWR;
    }

    if (oflag & fatIO_CREATE)
    {
        flags |= LFS_O_CREAT;
    }

    if (oflag & fatIO_EXCLUSIVE)
    {
        flags |= LFS_O_EXCL;
    }

    if (oflag & fatIO_TRUNCATE)
    {
        flags |= LFS_O_TRUNC;
    }

    if (oflag & fatIO_APPEND)
    {
        flags |= LFS_O_APPEND;
    }

    memset(&LfsFileDes[partition][Handle], 0x00, sizeof(lfs_sHandle));

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    cfg = lfs_init_file_cfg();

    result = lfs_file_opencfg(&(pDfsLfs->lfs), file, filename, flags, cfg);
    if (result != LFS_ERR_OK)
    {
        FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

        lfs_file_handle_cleanup(partition, Handle);
        lfs_unlock(lfs_mutex[partition]);

        return result;
    }

    NeedCheck = FALSE;
    for(i = 0; i < sizeof(lfs_white_list)/LFS_WHITE_LIST_LEN; i++)
	{
		if(strstr(filename, lfs_white_list[i]) != NULL)
		{
			NeedCheck = TRUE;
			break;
		}
	}

    if(NeedCheck)
    {
        LfsFileDes[partition][Handle].CkSum = LFS_CKSUM_ID;
    }

    LfsFileDes[partition][Handle].HeadID = LFS_HEAD_ID;
    LfsFileDes[partition][Handle].TailID = LFS_TAIL_ID;
    LfsFileDes[partition][Handle].oflag = LFS_FILE_ID;
    LfsFileDes[partition][Handle].Name = (char *)malloc(filenameLen + 1);
    strcpy(LfsFileDes[partition][Handle].Name, filename);

    if(!lfs_file_verify(EXT_FILE_HANDLE(Handle, partition), FALSE, partition))
    {
        result = lfs_file_close(&(pDfsLfs->lfs), file);

        LFSLogPrintf("lfs: Remove damaged file %s: result %d",  filename, result);

        lfs_remove(&(pDfsLfs->lfs), filename);

        if (oflag & fatIO_CREATE)
        {
            result = lfs_file_open(&(pDfsLfs->lfs), file, filename, flags);
            if (result != LFS_ERR_OK)
            {
                LFSLogPrintf("lfs: Fail to create %s: result %d", filename, result);

                lfs_file_handle_cleanup(partition, Handle);
                lfs_unlock(lfs_mutex[partition]);

                return result;
            }
        }
        else
        {
            lfs_file_handle_cleanup(partition, Handle);
            lfs_unlock(lfs_mutex[partition]);

            return LFS_ERR_NOENT;
        }
    }

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s[%s]: Handle %d", __FUNCTION__, filename, Handle);

    return EXT_FILE_HANDLE(Handle, partition);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_close                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function close a lfs file.                                   */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_close(int Handle)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    if(Handle < 0)
    {
        return LFS_ERR_BADF;
    }

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    lfs_file_verify(EXT_FILE_HANDLE(Handle, partition), TRUE, partition);

    result = lfs_file_close(&(pDfsLfs->lfs), file);

    lfs_file_handle_cleanup(partition, Handle);

    lfs_unlock(lfs_mutex[partition]);

    lfs_write_back(partition);

    FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_read                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read data from file.                                */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_read(int Handle, void* buf, UINT32 len)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int ssize = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    ssize = lfs_file_read(&(pDfsLfs->lfs), file, buf, len);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: ssize %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_readEx                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read data from file.                                */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_readEx(int Handle, void* buf, UINT32 len, UINT32 filepostoread)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int ssize = 0, soff = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    if(Handle < 0)
    {
        return LFS_ERR_BADF;
    }

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    soff = lfs_file_seek(&(pDfsLfs->lfs), file, filepostoread, LFS_SEEK_SET);
    if (soff < 0)
    {
        LFSLogPrintf("%s: lfs_file_seek soff %d", __FUNCTION__, soff);

        lfs_unlock(lfs_mutex[partition]);

        return soff;
    }

    ssize = lfs_file_read(&(pDfsLfs->lfs), file, buf, len);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: ssize %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_write                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function write data to file.                                 */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_write(int Handle, const void* buf, UINT32 len)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int ssize = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    ssize = lfs_file_write(&(pDfsLfs->lfs), file, buf, len);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: ssize %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_ftell                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the file position.                              */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_ftell(int Handle)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int ssize = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

	ssize = lfs_file_tell(&(pDfsLfs->lfs), file);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: ssize %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_writeEx                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function write data to file.                                 */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_writeEx(int Handle, const void* buf, UINT32 len, UINT32 filePostowrite)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int ssize = 0, soff = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    if(Handle < 0)
    {
        return LFS_ERR_BADF;
    }

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    soff = lfs_file_seek(&(pDfsLfs->lfs), file, filePostowrite, LFS_SEEK_SET);
    if (soff < 0)
    {
        LFSLogPrintf("%s: lfs_file_seek soff %d", __FUNCTION__, soff);

        lfs_unlock(lfs_mutex[partition]);

        return soff;
    }

    ssize = lfs_file_write(&(pDfsLfs->lfs), file, buf, len);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: ssize %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_lseek                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Move file pointer to specified location.            */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_lseek(int Handle, UINT32 offset, int whence)
{
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int soff = 0, partition = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    if(Handle < 0)
    {
        return LFS_ERR_BADF;
    }

    FATSYS_TRACE("%s[PTN %d]: Handle %d, offset %lu", __FUNCTION__, partition, Handle, offset);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    soff = lfs_file_seek(&(pDfsLfs->lfs), file, offset, whence);
    if (soff < 0)
    {
        LFSLogPrintf("%s: lfs_file_seek soff %d", __FUNCTION__, soff);

        lfs_unlock(lfs_mutex[partition]);

        return soff;
    }

    lfs_unlock(lfs_mutex[partition]);

    return file->pos;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_size                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get file size.                                      */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
UINT32 lfs_io_size(int Handle)
{
    UINT32 ssize = 0;
    int partition = 0;
    lfs_file_t *file = NULL;
    dfs_lfs_t *pDfsLfs = NULL;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    file = &(LfsFileDes[partition][Handle].u.LfsFd.file);

    ssize = lfs_file_size(&(pDfsLfs->lfs), file);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: size %d", __FUNCTION__, ssize);

    return ssize;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_eof                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function to judge if it is the end of file                   */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_eof(int Handle)
{
    int partition = 0;
    UINT32 ssize = 0, pos = 0;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    ssize = LfsFileDes[partition][Handle].u.LfsFd.file.ctz.size;
    pos = LfsFileDes[partition][Handle].u.LfsFd.file.pos;

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: size %d, pos %d", __FUNCTION__, ssize,pos);

	return ((pos >= ssize) ? 1 : 0);

}


/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_remove                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function remove a file from file system.                     */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_remove(const char* path)
{
    int result = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    int partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s: %s", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    path += lfs_get_prefixlen(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    result = lfs_remove(&(pDfsLfs->lfs), path);

    lfs_unlock(lfs_mutex[partition]);

    lfs_write_back(partition);

    FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_rename                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function rename a file in file system.                       */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_rename(const char* from, const char* to)
{
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s: %s -> %s", __FUNCTION__, from, to);

    partition = lfs_get_partition(from);

    from += lfs_get_prefixlen(from);

    to += lfs_get_prefixlen(to);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    result = lfs_rename(&(pDfsLfs->lfs), from, to);

    lfs_unlock(lfs_mutex[partition]);

    lfs_write_back(partition);

    FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_to_fatstat                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function translate file state to fat state                   */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void lfs_to_fatstat(fatTYPE_sStat *st, struct lfs_info* info)
{
    memset(st, 0, sizeof(fatTYPE_sStat));

    /* convert to dfs stat structure */
    st->st_size = info->size;

    switch (info->type)
    {
        case LFS_TYPE_DIR:
            st->st_mode = fatTYPE_DIR;
            break;

        case LFS_TYPE_REG:
            st->st_mode = fatTYPE_NORMAL;
            break;

        default:
            st->st_mode = fatTYPE_NORMAL;
            break;
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_stat                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read LFS file state.                                */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_stat(const char* path, fatTYPE_sStat *st)
{
    struct lfs_info info;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s: %s", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    path += lfs_get_prefixlen(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    result = lfs_stat(&(pDfsLfs->lfs), path, &info);
    if (result != LFS_ERR_OK)
    {
        lfs_unlock(lfs_mutex[partition]);

        LFSLogPrintf("lfs_io_stat %s result %d", path, result);

        return result;
    }

    lfs_unlock(lfs_mutex[partition]);

    lfs_to_fatstat(st, &info);

    FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

    return 0;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_Access                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function access a LFS file.                                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_Access(const char *path, UINT32 mode)
{
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    LFS_TRACE("%s: %s", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    path += lfs_get_prefixlen(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    result = lfs_access(&(pDfsLfs->lfs), path);

    lfs_unlock(lfs_mutex[partition]);

    LFS_TRACE("%s: result %d", __FUNCTION__, result);

    return result;
}


/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_statfs                                                    */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get file statfs.                                    */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_statfs(const char *path, UINT32 *Bytes)
{
    lfs_size_t in_use = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    if(!Bytes)
    {
        return LFS_ERR_INVAL;
    }

    FATSYS_TRACE("%s", __FUNCTION__);

    partition = lfs_get_partition(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    /* Get total sectors and free sectors */
    in_use = lfs_fs_size(&(pDfsLfs->lfs));

    lfs_unlock(lfs_mutex[partition]);

    *Bytes = (pDfsLfs->lfs.cfg->block_count - in_use) * pDfsLfs->lfs.cfg->block_size;

    FATSYS_TRACE("lfs: free space %lu bytes", *Bytes);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_used                                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the used bytes of LFS.                          */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_used(const char *path, UINT32 *Bytes)
{
    lfs_ssize_t in_use = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    if(!Bytes)
    {
        return LFS_ERR_INVAL;
    }

    FATSYS_TRACE("%s", __FUNCTION__);

    partition = lfs_get_partition(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    /* Get total sectors and free sectors */
    in_use = lfs_fs_size(&(pDfsLfs->lfs));

    lfs_unlock(lfs_mutex[partition]);

    *Bytes = in_use * pDfsLfs->lfs.cfg->block_size;

    FATSYS_TRACE("%s: %lu bytes", __FUNCTION__, *Bytes);

    return result;
}

 /*************************************************************************/
 /*                                                                       */
 /* FUNCTION                                                              */
 /*                                                                       */
 /*      lfs_check_block_validity                                         */
 /*                                                                       */
 /* DESCRIPTION                                                           */
 /*                                                                       */
 /*      The function check the LFS block validity.                       */
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
 /*      block                                                            */
 /*      buffer                                                           */
 /*                                                                       */
 /* OUTPUTS                                                               */
 /*                                                                       */
 /*      None                                N/A                          */
 /*                                                                       */
 /*************************************************************************/
int lfs_check_block_validity(void *p, lfs_block_t block)
{
    lfs_t *lfs = p;
    UINT32 grp = 0, bit = 0;
    int i = 0, partition = 0;
    dfs_lfs_t *pDfsLfs = NULL;
    lfsBlkMapType *pBlkMap = NULL;
    lfs_flash_info *pInfo = NULL;

/*---------------------------------------------------------------------*/

    for (i = 0; i < NUM_OF_PARTITION; i++)
    {
        pDfsLfs = &dfs_lfs[i];

        if (lfs == &pDfsLfs->lfs)
        {
            partition = i;
        }
    }

    pBlkMap = GetLfsBlockMapInfo(partition);
    pInfo = (lfs_flash_info *)(lfs->cfg->context);

    grp = block >> 0x05;
	bit = block & 0x1F;

	FATSYS_TRACE("%s[PTN %d]: block 0x%x, LfsGrpCnt 0x%x", __FUNCTION__, partition, block, pBlkMap->LfsGrpCnt);

    if(block >= lfs->cfg->block_count)
    {
        LFSLogPrintf("%s: Invalid block 0x%lx", __FUNCTION__, block);
        return LFS_ERR_BLOCK;
    }

    /* Check whether there are duplicate blocks or not */
    if(!(pBlkMap->LfsBlkTbl[grp] & (0x01 << bit)))
    {
        pBlkMap->LfsBlkTbl[grp] |= (0x01 << bit);
    }
    else
    {
        LFSLogPrintf("%s: Find duplicate block 0x%x",  __FUNCTION__, block);
        return LFS_ERR_EXIST;
    }

    return LFS_ERR_OK;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_sys_traverse                                                 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function do lfs system traverse.                             */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_sys_traverse(const char *path)
{
    dfs_lfs_t *pDfsLfs = NULL;
    lfsBlkMapType *pBlkMap = NULL;
    int status = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s %s", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    pBlkMap = GetLfsBlockMapInfo(partition);

    ASSERT((pBlkMap->Alloc == FALSE) && (pBlkMap->LfsBlkTbl != NULL));

    /* Traverse lfs system and check block validity. */
    status = lfs_fs_traverse(&(pDfsLfs->lfs), lfs_check_block_validity, &(pDfsLfs->lfs), FALSE);
    if(status != LFS_ERR_OK)
    {
        LFSLogPrintf("%s: error %d",  __FUNCTION__, status);

        if(status == LFS_ERR_EXIST)
        {
            status = lfs_mkdir(&(pDfsLfs->lfs), "tmp");
            LFSLogPrintf("%s: mk temp dir %d",  __FUNCTION__, status);
            if (status)
            {
                goto cleanup;
            }

            status = lfs_remove(&(pDfsLfs->lfs), "tmp");
            LFSLogPrintf("%s: remove temp dir %d",  __FUNCTION__, status);
            if (status)
            {
                goto cleanup;
            }

            memset((UINT8 *)pBlkMap->LfsBlkTbl, 0x00, pBlkMap->LfsGrpCnt * sizeof(UINT32));
            status = lfs_fs_traverse(&(pDfsLfs->lfs), lfs_check_block_validity, &(pDfsLfs->lfs), FALSE);
        }

    }

cleanup:

    /* Reset Lfs block table. */
    if (LfsFlashInfo[partition].useCache)
    {
        memset((UINT8 *)pBlkMap->LfsBlkTbl, 0x00, pBlkMap->LfsGrpCnt * sizeof(UINT32));
    }
    else
    {
        free(pBlkMap->LfsBlkTbl);
        pBlkMap->LfsBlkTbl = NULL;
    }

    lfs_unlock(lfs_mutex[partition]);

    return status;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_dir_open                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Open or create a directory.                         */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_dir_open(const char *path)
{
    lfs_dir_t *dir = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, Handle = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s[%s]", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    path += lfs_get_prefixlen(path);

    Handle = lfs_get_freehandle(partition);
    if(Handle < 0)
    {
        lfs_unlock(lfs_mutex[partition]);
        return Handle;
    }

    memset(&LfsFileDes[partition][Handle], 0x00, sizeof(lfs_sHandle));

    dir = &(LfsFileDes[partition][Handle].u.DirFd.dir);

    result = lfs_dir_open(&(pDfsLfs->lfs), dir, path);
    if (result != LFS_ERR_OK)
    {
        lfs_unlock(lfs_mutex[partition]);
        return result;
    }

    LfsFileDes[partition][Handle].HeadID = LFS_HEAD_ID;
    LfsFileDes[partition][Handle].TailID = LFS_TAIL_ID;
    LfsFileDes[partition][Handle].oflag = LFS_DIR_ID;

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s[%s]: Handle %d", __FUNCTION__, path, Handle);

    return EXT_FILE_HANDLE(Handle, partition);
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_dir_read                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function read file from a directory.                         */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_dir_read(int Handle, struct lfs_info *info)
{
    lfs_dir_t *dir = NULL;
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, partition = 0;

/*---------------------------------------------------------------------*/

    ASSERT(info != NULL);

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    dir = &(LfsFileDes[partition][Handle].u.DirFd.dir);

    result = lfs_dir_read(&(pDfsLfs->lfs), dir, info);

    lfs_unlock(lfs_mutex[partition]);

    FATSYS_TRACE("%s: result %d, type 0x%x, size 0x%x, name[0] 0x%x",
                 __FUNCTION__, result, info->type, info->size, info->name[0]);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_io_dir_close                                                 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function close a directory.                                  */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_dir_close(int Handle)
{
    int result = 0, partition = 0;
    lfs_dir_t *dir = NULL;
    dfs_lfs_t *pDfsLfs = NULL;

/*---------------------------------------------------------------------*/

    partition = Get_Partition_From_Handle(Handle);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    Handle = lfs_valid_handle(Handle, partition);
    ASSERT(Handle >= 0);

    FATSYS_TRACE("%s[PTN %d]: Handle %d", __FUNCTION__, partition, Handle);

    dir = &(LfsFileDes[partition][Handle].u.DirFd.dir);

    result = lfs_dir_close(&(pDfsLfs->lfs), dir);

    lfs_file_handle_cleanup(partition, Handle);

    lfs_unlock(lfs_mutex[partition]);

    lfs_write_back(partition);

    return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_dir_make                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function create a directory.                                 */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_io_dir_make(const char *path)
{
    dfs_lfs_t *pDfsLfs = NULL;
    int result = 0, Handle = 0, partition = 0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s[%s]", __FUNCTION__, path);

    partition = lfs_get_partition(path);

    lfs_lock(lfs_mutex[partition]);

    pDfsLfs = &dfs_lfs[partition];

    path += lfs_get_prefixlen(path);

	result = lfs_mkdir(&(pDfsLfs->lfs), path);

    lfs_unlock(lfs_mutex[partition]);

    lfs_write_back(partition);

	FATSYS_TRACE("%s: result %d", __FUNCTION__, result);

	return result;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      lfs_fname_match                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function Checks to see if filenames match, including         */
/*      wildcards.                                                       */
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
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
int lfs_fname_match(const char *src, const char *dest)
{
   const char *src_ptr  = src;   /* pointer to parse src string */
   const char *dest_ptr = dest;  /* pointer to parse dest string */

/*---------------------------------------------------------------------*/

   do	/* loop through dest */
   {
	  /* check for multiple character wildcard */
	  if (*dest_ptr == LFS_MCWILDCARD)
	  {
		 /* skip by multiple character and
			repeated multiple character wildcards */
		 while (*dest_ptr == LFS_MCWILDCARD)
		 {
			dest_ptr++;
		 }

		 /* if at the end of dest then must be a match */
		 if (*dest_ptr == LFS_EOS)
		 {
			return TRUE;
		 }

		 /* parse through src looking for match */
		 while (*src_ptr != LFS_EOS)
		 {
			if (lfs_fname_match(src_ptr, dest_ptr) == TRUE)
			{
			   return TRUE;
			}
			/* not a match, try next character in src */
			src_ptr++;
		 }

		 /* no match after multiple character wildcard found */
		 return FALSE;
	  }
	  else	/* not multiple character wildcard */
	  {
		 /* check if character matches */
		 if ((*dest_ptr != *src_ptr) && (*dest_ptr != LFS_SCWILDCARD))
		 {
			return FALSE;
		 }

		 /* make sure if the single character wildcard
			that src isn't at end */
		 if ((*dest_ptr == LFS_SCWILDCARD) && (*src_ptr == LFS_EOS))
		 {
			return FALSE;
		 }

		 /* on to next character... */
		 src_ptr++;
		 dest_ptr++;
	  }

   } while (*dest_ptr != LFS_EOS);

   /* make sure parsed all of src */
   return (*src_ptr == LFS_EOS);
}

