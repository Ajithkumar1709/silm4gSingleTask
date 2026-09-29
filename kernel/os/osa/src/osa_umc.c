/*************************************************************************/
/*                                                                       */
/*               Copyright Mentor Graphics Corporation 2012              */
/*                         All Rights Reserved.                          */
/*                                                                       */
/* THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION WHICH IS  */
/* THE PROPERTY OF MENTOR GRAPHICS CORPORATION OR ITS LICENSORS AND IS   */
/* SUBJECT TO LICENSE TERMS.                                             */
/*                                                                       */
/*************************************************************************/

/*************************************************************************/
/*                                                                       */
/* FILE NAME                                               VERSION       */
/*                                                                       */
/*      umc.c                                          Nucleus PLUS 1.15 */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/*      UM - USB Ring Management                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This file contains the core routines for the USB Ring Memory     */
/*      Management component.                                            */
/*                                                                       */
/* DATA STRUCTURES                                                       */
/*                                                                       */
/*      None                                                             */
/*                                                                       */
/* FUNCTIONS                                                             */
/*                                                                       */
/*      UMC_Data_Buffer_Init              Create a usb ring memory pool  */
/*      UMC_Data_Buffer_Get               Allocate memory from the       */
/*                                        specified the memory pool      */
/*      UMC_Data_Buffer_Put               Release memory from the        */
/*                                        specified the memory pool      */
/*      UMC_Data_Buffer_Put_Stall         Release memory from the        */
/*                                        specified the memory pool      */
/*      UMC_Data_Buffer_Get_Block         Get a block from the full      */
/*                                        block list                     */
/*      UMC_Data_Buffer_Put_Block         Put the block to the empty     */ 
/*                                        block list                     */
/*      UMC_Data_Buffer_Get_Size          Reture the size of bytes       */
/*                                        waiting to be sent             */
/*                                                                       */
/* DEPENDENCIES                                                          */
/*                                                                       */
/*      cs_extr.h                           Common Service functions     */
/*      tc_extr.h                           Thread Control functions     */
/*      um_extr.h                           Partition functions          */
/*      hi_extr.h                           History functions            */
/*                                                                       */
/*************************************************************************/
#define         NU_SOURCE_FILE

#define NU_DMC_SEARCH_PTR_PATCH
#define UL_IP_DATA_OPT
#define UL_IP_DATA_LEN	48

#ifdef PLAT_USE_THREADX
#include		"osa.h"
#include        "osa_um_extr.h"        /* Dynamic memory functions  */
#else
#include        "cs_extr.h"        /* Common service functions  */
#include        "tc_extr.h"        /* Thread control functions  */
#include        "um_extr.h"        /* Dynamic memory functions  */
#include        "hi_extr.h"        /* History functions         */
#endif

#ifdef PLAT_USE_THREADX
#define DB_LOCK_INIT       UINT32 cpsr;     //UNSIGNED level
#define DB_LOCK_DISABLE    cpsr = disableInterrupts(); 		//level = disableInterrupts()
#define DB_LOCK_ENABLE     restoreInterrupts(cpsr);      //restoreInterrupts(level)
#else
#define DB_LOCK_INIT                             //UNSIGNED level
#define DB_LOCK_DISABLE    TCT_System_Protect(); //level = disableInterrupts()
#define DB_LOCK_ENABLE     TCT_Unprotect();      //restoreInterrupts(level)
#endif

#define DATABLOCK(buffer, n)     \
    (UM_BLOCK*)(buffer->um_data_ptr + n * buffer->um_block_size)
#define UPDATABLOCK(buffer, n)     \
    (UMUP_BLOCK*)(buffer->um_data_ptr + n * buffer->um_block_size)
#define PACKETALLIGNSIZE (8)
#define PACKETALLIGNMASK (0xfffffff8)
#define PACKETALLIGUNNMASK ((UINT32)0x7)

#include <osa.h>
#include <log.h>
#include <bsp.h>
#define UMC_MOD "[UMC ]"

#define PACKET_ALIGN(size, align)	(((size) + (align - 1)) & ~(align - 1))
UINT16 CurGetIndex=0;

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Init                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function creates a usb ring memory pool and then places it  */
/*      on the list of created usb ring memory pools.                    */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      DMCE_Create_Memory_Pool             Error checking shell         */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      hdr                                 Memory pool block header     */
/*      ptr                                 Starting address of the pool */
/*      block_size                          Number of bytes in the block */
/*      block_num                           Number of blocks in the pool */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      NU_SUCCESS                                                       */
/*                                                                       */
/*************************************************************************/

STATUS UMC_Data_Buffer_Init(UM_PCB *buf, DATA_ELEMENT *hdr, DATA_ELEMENT *ptr, UINT16 block_size, UINT16 block_num)
{
    UNSIGNED index;
    volatile UM_BLOCK* block = NULL;

	/* initialize buffer header */
    buf->um_hdr = (UM_BLOCK_HDR*)hdr;
    buf->um_hdr->um_put_index = 0;
    buf->um_hdr->um_get_index = 0;
	
	CurGetIndex=buf->um_hdr->um_get_index; //for Nezha2 USB optimization
    buf->um_data_ptr = ptr;
    buf->um_block_num = block_num;
    buf->um_block_size = block_size;

    buf->um_waiting_lwm = 0;
    buf->um_lwm = block_num / 3;

    buf->um_tx_notify = NULL;
    buf->um_resume_notify = NULL;

	log_set_module_level(UMC_MOD, LOG_DEBUG_VALUE);
	log_printf(LOG_DEBUG UMC_MOD "Init UMC buffer, hdr 0x%08x, pool 0x%08x\n",
		hdr, ptr);
    /* initialize block */
    for (index = 0; index < block_num; index ++)
    {
        block = DATABLOCK(buf, index);
        block->um_length = sizeof(UM_BLOCK);
        block->um_ref = 0;
    }

	/* Return successful completion.  */
    return(OS_SUCCESS);
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Get                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function allocates memory from the specified the memory     */
/*      pool.  If the memory is currently available, this function       */
/*      is completed immediately.  Otherwise, if there is not enough     */
/*      memory currently available, task suspension is possible.         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get             Error checking shell             */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      size                                Number of bytes to be        */
/*                                              allocated                */
/*      newblock                            whether allocates the memory */
/*                                              from a new block         */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Data Pointer                                                     */
/*                                                                       */
/*************************************************************************/

DATA_ELEMENT *UMC_Data_Buffer_Get(UM_PCB *buf, UINT16 size, OPTION newblock)
{
    DB_LOCK_INIT;
    DATA_ELEMENT* ptr;
    DATA_ELEMENT* block_ptr;
    UINT16 next_index;
    UM_BLOCK* block;
    VOID (*tx_notify)(UM_PCB* buffer);

    ptr = NULL;
    tx_notify = NULL;

	if(size> buf->um_block_size)
	{
		log_printf(LOG_ERR UMC_MOD "invalid block size\n");
		return NULL;
	}
	
	//log_printf(LOG_DEBUG UMC_MOD "get buffer, get_index: %d, put_index: %d\n", 
	//	buf->um_hdr->um_get_index, buf->um_hdr->um_put_index);
	if (buf->um_event_handler != NULL)
		buf->um_event_handler(buf, UM_EVT_GET_BUF);
    DB_LOCK_DISABLE;
    block = DATABLOCK(buf, buf->um_hdr->um_put_index);

	// log_printf(LOG_DEBUG UMC_MOD"block[0x%08x] length: %d, block size: %d, size: %d\n", 
	//	block, block->um_length, buf->um_block_size, size);
	log_printf(LOG_ERR UMC_MOD"UMC_Data_Buffer_Get get idx: %d put idx:%d, ref:%d,size:%d\r\n", buf->um_hdr->um_get_index, buf->um_hdr->um_put_index,block->um_ref,size);

	if ((block->um_length + size) > buf->um_block_size)
	{
        /* move to next block */
        if (block->um_ref == 0)
            tx_notify = buf->um_tx_notify;

		
        next_index = buf->um_hdr->um_put_index + 1;
        if (next_index >= buf->um_block_num) next_index = 0;

        if (next_index != buf->um_hdr->um_get_index)
        {
            buf->um_hdr->um_put_index = next_index;
			block->um_length -= sizeof(UM_BLOCK);
			
        }
        else
        {
            /* set hwm flag */
            buf->um_waiting_lwm = 1;

            /* no block anymore */
            DB_LOCK_ENABLE;
			log_printf(LOG_ERR UMC_MOD"HWM, no memory block\n");
            return NULL;
        }

        /* re-get block */
        block = DATABLOCK(buf, buf->um_hdr->um_put_index);
        block->um_length = sizeof(UM_BLOCK);
        block->um_ref = 0;
		log_printf(LOG_ERR UMC_MOD"move to next block get idx: %d put idx:%d\r\n", buf->um_hdr->um_get_index, buf->um_hdr->um_put_index);
    }

    block_ptr = (DATA_ELEMENT*)block;
    ptr = &block_ptr[block->um_length];
    block->um_length += size;

    block->um_ref ++;
    DB_LOCK_ENABLE;


    if (tx_notify != NULL)
        tx_notify(buf);
	log_printf(LOG_ERR UMC_MOD"UMC_Data_Buffer_Get return ptr : 0x%lx\r\n", ptr);

    return ptr;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Put                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function release the memory to the specified the memory     */
/*      pool. This means the momory was filled with data, and can be     */
/*      sent.                                                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Put                   Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      ptr                                 pointer of bytes to be       */
/*                                              released                 */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                                             */
/*                                                                       */
/*************************************************************************/

VOID UMC_Data_Buffer_Put(UM_PCB *buf, DATA_ELEMENT *ptr)
{
    DB_LOCK_INIT;
    UINT16 block_index;
    UM_BLOCK* block;
    VOID (*tx_notify)(UM_PCB* buffer);

    tx_notify = NULL;
    block_index = (ptr - buf->um_data_ptr)/buf->um_block_size;
    block = DATABLOCK(buf, block_index);

	// log_printf(LOG_DEBUG UMC_MOD"put buffer: 0x%08x, block refcount %d\n", ptr, block->um_ref);

	//log_printf(LOG_DEBUG UMC_MOD"put buffer: 0x%08x, block length %d, ref %d\n", 
	//	ptr, block->um_length, block->um_ref);
	if (buf->um_event_handler != NULL)
		buf->um_event_handler(buf, UM_EVT_PUT_BUF);
    DB_LOCK_DISABLE;
	
    block->um_ref --;
	log_printf(LOG_ERR UMC_MOD"UMC_Data_Buffer_Put ptr :0x%x\r\n",ptr);
	log_printf(LOG_ERR UMC_MOD"UMC_Data_Buffer_Put get idx: %d put idx:%d, ref:%d, block idx: %d\r\n", buf->um_hdr->um_get_index, buf->um_hdr->um_put_index,block->um_ref,block_index);
    if (block->um_ref == 0)
    {
    	// log_printf(LOG_DEBUG UMC_MOD "block index:%d, get_index %d, put_index %d\n", 
		//	block_index, buf->um_hdr->um_get_index, buf->um_hdr->um_put_index);

        if (block_index != buf->um_hdr->um_put_index)
        {
            tx_notify = buf->um_tx_notify;
			// log_printf(LOG_DEBUG UMC_MOD "notfiy tx, for different block\n");
        }
        else if (buf->um_hdr->um_put_index == buf->um_hdr->um_get_index)
        {
            UINT16 next_index;
            next_index = buf->um_hdr->um_put_index + 1;
            if (next_index >= buf->um_block_num) next_index = 0;

            buf->um_hdr->um_put_index = next_index;
			// log_printf(LOG_DEBUG UMC_MOD"move to next block:%d\n", buf->um_hdr->um_put_index);
			// block->um_length = PACKET_ALIGN(block->um_length, 8);
			block->um_length -= sizeof(UM_BLOCK);

			/* move to next block */
			block = DATABLOCK(buf, buf->um_hdr->um_put_index);
			block->um_length = sizeof(UM_BLOCK);
			block->um_ref = 0;

            tx_notify = buf->um_tx_notify;
        }

		else
		{
			log_printf(LOG_ERR UMC_MOD"not send notify!!\r\n");

		}
    }
    DB_LOCK_ENABLE;
    if (tx_notify != NULL)
    {
        tx_notify(buf);
    }
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Get_Block                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function gets a block from the full block list.             */ 
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get_Block             Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      UM_BLOCK*                           The pointer of a full block  */
/*                                                                       */
/*************************************************************************/

UM_BLOCK* UMC_Data_Buffer_Get_Block(UM_PCB *buf)
{
    DB_LOCK_INIT;
    UM_BLOCK* block = NULL;

	DB_LOCK_DISABLE;
    if (buf->um_hdr->um_get_index == buf->um_hdr->um_put_index)
    {
    	/* empty */
        DB_LOCK_ENABLE;
        return block;
    }

    block = DATABLOCK(buf, buf->um_hdr->um_get_index);
    if (block->um_ref != 0)
    {
        block = NULL;
    }
    DB_LOCK_ENABLE;

    return block;
}

UM_BLOCK* UMC_Data_Buffer_Get_Block_Nezha2(UM_PCB *buf)
{
//    DB_LOCK_INIT;
    UM_BLOCK* block = NULL;

//	DB_LOCK_DISABLE;
    if (CurGetIndex == buf->um_hdr->um_put_index)
    {
    	/* empty */
//        DB_LOCK_ENABLE;
        return block;
    }

    block = DATABLOCK(buf, CurGetIndex);
    if (block->um_ref != 0)
    {
        block = NULL;
    }else{
		CurGetIndex += 1;
        if (CurGetIndex >= buf->um_block_num) CurGetIndex = 0;

	}
//    DB_LOCK_ENABLE;
 //   uart_printf("get %d, put %d\r\n",CurGetIndex,buf->um_hdr->um_put_index);
    return block;
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Put_Block                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function puts the block to the empty block list.            */ 
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Put_Block             Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      block                               Memory block pointer         */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                                             */
/*                                                                       */
/*************************************************************************/

VOID UMC_Data_Buffer_Put_Block(UM_PCB *buf, UM_BLOCK *block)
{
    DB_LOCK_INIT;
    UINT16 block_index;
    VOID (*resume_notify)(UM_PCB* buffer);

    if (block == NULL) return ;

    resume_notify = NULL;

    DB_LOCK_DISABLE;
    /* get block index */
    block_index = ((UNSIGNED)block - (UNSIGNED)buf->um_data_ptr)/buf->um_block_size;
	
    if (block_index == buf->um_hdr->um_get_index)
    {
        buf->um_hdr->um_get_index += 1;
        if (buf->um_hdr->um_get_index >= buf->um_block_num) buf->um_hdr->um_get_index = 0;
    }
	
    if (buf->um_waiting_lwm)
    {
        UINT16 block_num;

        block_num = buf->um_block_num + buf->um_hdr->um_put_index - buf->um_hdr->um_get_index;
        block_num = block_num % buf->um_block_num;
        if (block_num < buf->um_lwm)
        {
            resume_notify = buf->um_resume_notify;
            buf->um_waiting_lwm = 0;
        }
    }
    DB_LOCK_ENABLE;
//	log_printf(LOG_DEBUG UMC_MOD"put block[%d][g %d][p %d]:%08x\n", 
//		block_index,  
//		buf->um_hdr->um_get_index,	
//		buf->um_hdr->um_put_index, 
//		(UINT32)block);

    if (resume_notify != NULL)
    {
        resume_notify(buf);
    }
}
VOID UMC_Data_Buffer_Put_Block_nezha2(UM_PCB *buf, UM_BLOCK *block)
{
//    DB_LOCK_INIT;
    UINT16 block_index;
//    VOID (*resume_notify)(UM_PCB* buffer);

    if (block == NULL) return ;

//    resume_notify = NULL;

   // DB_LOCK_DISABLE;
    /* get block index */
    block_index = ((UNSIGNED)block - (UNSIGNED)buf->um_data_ptr)/buf->um_block_size;
	
    if (block_index == buf->um_hdr->um_get_index)
    {
        buf->um_hdr->um_get_index += 1;
        if (buf->um_hdr->um_get_index >= buf->um_block_num) buf->um_hdr->um_get_index = 0;
		block->um_length=0;
		block->um_ref=0;
    }else{
//		log_printf(LOG_ERR UMC_MOD"put block error index %d, expected index %d\n",block_index, buf->um_hdr->um_get_index);

	}
	
    if (buf->um_waiting_lwm)
    {
        UINT16 block_num;

        block_num = buf->um_block_num + buf->um_hdr->um_put_index - buf->um_hdr->um_get_index;
        block_num = block_num % buf->um_block_num;
        if (block_num < buf->um_lwm)
        {
//            resume_notify = buf->um_resume_notify;
            buf->um_waiting_lwm = 0;
        }
    }
    //DB_LOCK_ENABLE;
/*	log_printf(LOG_DEBUG UMC_MOD"put block[%d][g %d][p %d]:%08x\n", 
		block_index,  
		buf->um_hdr->um_get_index,	
		buf->um_hdr->um_put_index, 
		(UINT32)block);
	uart_printf("put block[%d][g %d][p %d]:%08x\n", 
		block_index,  
		buf->um_hdr->um_get_index,	
		buf->um_hdr->um_put_index, 
		(UINT32)block);*/

	/*Fixed coverity[dead_error_line]*/
	#if 0
    if (resume_notify != NULL)
    {
        resume_notify(buf);
    }
	#endif
}


/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      Umc_Is_Reach_Hwm                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function check the remained free memory block in the memory pool*/
/*      compared with a pre-configure HWM value, if reach the HWM return TURE     */

/*                                                                       */
/* CALLED BY                                                             */
/* PS use this API to check whether low layer shared memory is almost used out. */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */

/*************************************************************************/

BOOL Umc_Is_Reach_Hwm(UM_PCB *buf)
	{
		DB_LOCK_INIT;
	
		UINT16 next_index;
		signed int num_free_block;
	
		if (buf->um_event_handler != NULL)
			buf->um_event_handler(buf, UM_EVT_GET_BUF);
	
		DB_LOCK_DISABLE
	
		next_index = buf->um_hdr->um_put_index + 1;//get AP read ptr
		if (next_index >= buf->um_block_num) next_index = 0;
		
		num_free_block=buf->um_hdr->um_get_index-next_index;//get cp allocated ptr
		if(num_free_block<0) num_free_block+=buf->um_block_num;
	
		DB_LOCK_ENABLE
	
		if(num_free_block<= (buf->um_block_num*5/100))// less than %5 block remained, currenttly 64 blocks, 5% is 3 blocks
		{
			log_printf(LOG_ERR UMC_MOD"UMC_IS_REACH_HWM, num of free memory block %d\n",num_free_block);

			return TRUE;
		}
		else
			return FALSE;
		
	 
	}



/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Get_Size                                         */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function gives the size of bytes waiting to be sent         */ 
/*      in the buffer.                                                   */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get_Size             Error checking shell        */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      UNSIGNED                            The size of bytes waiting    */
/*                                            to be sent                 */
/*                                                                       */
/*************************************************************************/

UNSIGNED UMC_Data_Buffer_Get_Size(UM_PCB *buf)
{
    DB_LOCK_INIT;
    UNSIGNED  index;
    UNSIGNED  total_length = 0;
    UM_BLOCK* block = NULL;

    DB_LOCK_DISABLE;
    for (index = buf->um_hdr->um_get_index; index != buf->um_hdr->um_put_index; )
    {
        block = DATABLOCK(buf, index);
        total_length += block->um_length;

        index ++;
        if (index > buf->um_block_num)
        {
            index = 0;
        }
    }
    DB_LOCK_ENABLE;

    return total_length;
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMC_Data_Buffer_Get_Size                                         */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function gives the size of bytes waiting to be sent         */ 
/*      in the buffer.                                                   */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get_Size             Error checking shell        */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      UNSIGNED                            The size of bytes waiting    */
/*                                            to be sent                 */
/*                                                                       */
/*************************************************************************/

UNSIGNED UMC_Data_Buffer_Is_Full(UM_PCB *buf)
{
    DB_LOCK_INIT;
    UNSIGNED  next_index;
    UNSIGNED  is_full = 0;

    DB_LOCK_DISABLE;

	next_index = buf->um_hdr->um_put_index + 1;
    if (next_index >= buf->um_block_num) next_index = 0;

    if (next_index != buf->um_hdr->um_get_index)
    {
           is_full=0;
    }
    else
    {
           is_full=1;
    }
	DB_LOCK_ENABLE;
	return is_full;
}

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMUPC_Data_Buffer_Init                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function creates a usb ring memory pool and then places it  */
/*      on the list of created usb ring memory pools.                    */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      DMCE_Create_Memory_Pool             Error checking shell         */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      hdr                                 Memory pool block header     */
/*      ptr                                 Starting address of the pool */
/*      block_size                          Number of bytes in the block */
/*      block_num                           Number of blocks in the pool */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      NU_SUCCESS                                                       */
/*                                                                       */
/*************************************************************************/

STATUS UMUPC_Data_Buffer_Init(UMUP_PCB *buf, DATA_ELEMENT *hdr, DATA_ELEMENT *ptr, UINT16 block_size, UINT16 block_num)
{
    UNSIGNED index;
    UMUP_BLOCK* block = NULL;

    buf->um_hdr = (UMUP_BLOCK_HDR*)hdr;
    buf->um_hdr->um_block_put_index = 0;
    buf->um_hdr->um_block_get_index = 0;
    buf->um_hdr->um_buffer_put_index = 0;
	buf->um_hdr->um_buffer_get_index = 0;
    buf->um_data_ptr = ptr;
    buf->um_block_num = block_num;
    buf->um_block_size = block_size;

	buf->um_block_by_application= 0;
    buf->um_waiting_lwm = 0;
    buf->um_lwm = block_num / 3;

    buf->um_rx_notify = NULL;
    buf->um_resume_notify = NULL;

    /* initialize block */
    for (index = 0; index < block_num; index ++)
    {
        block = UPDATABLOCK(buf, index);
		//log_printf(LOG_INFO"block[%d]=> 0x%08x\n", index, block);
        block->um_length = sizeof(UM_BLOCK);
        block->um_ref = 0;
		block->umup_ref= 0;
    }

	/* Return successful completion.  */
	//log_printf("up link data buffer initilization sucessfull\r\n");
    return(OS_SUCCESS);
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMUPC_Data_Buffer_Get_Block                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function gets a block from the full block list.             */ 
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get_Block             Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      UM_BLOCK*                           The pointer of a full block  */
/*                                                                       */
/*************************************************************************/

UMUP_BLOCK* UMUPC_Data_Buffer_Get_Block(UMUP_PCB *buf)
{
    DB_LOCK_INIT;
	UINT16 block_index;
    UMUP_BLOCK* block = NULL;

    DB_LOCK_DISABLE;
	if((buf->um_block_by_application==1)||(buf->um_waiting_lwm ==1))
	{
        /* no block anymore */
        DB_LOCK_ENABLE;
		//log_printf("uplink get block return null by application\r\n");        
        return block;
    }
	block_index=buf->um_hdr->um_block_get_index+1;
	if (block_index >= buf->um_block_num) block_index = 0;

	if (block_index == buf->um_hdr->um_buffer_put_index)
    {
    	/* empty */   
        /* set hwm flag */
        buf->um_waiting_lwm = 1;

        /* no block anymore */
        DB_LOCK_ENABLE;
		//log_printf("up stream allocate block failed , reach high water mask\r\n");        
        return block;
    }

	
    block = UPDATABLOCK(buf, block_index);
	//log_printf("up stream get block[%d][%d]: ref:%d\n", block_index, buf->um_hdr->um_put_index, block->um_ref);

	block->um_ref = 0;
    block->umup_ref= 0;
	block->um_length=sizeof(UMUP_BLOCK);
	buf->um_hdr->um_block_get_index=block_index;

    DB_LOCK_ENABLE;

	/*Fixed coverity[check_after_deref]*/
	#if 0
	if (block != NULL)
	{
		//log_printf("<-get block[%d]: 0x%08x\n", block_index, block);
	}
	#endif
	
    return block;
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMUPC_Data_Buffer_Put_Block                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function puts the block to the empty block list.            */ 
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Put_Block             Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      block                               Memory block pointer         */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                                             */
/*                                                                       */
/*************************************************************************/
STATUS UMUPC_Data_Buffer_Put_Block(UMUP_PCB *buf, UMUP_BLOCK *block, UINT16 size)
{
    DB_LOCK_INIT;
//    UINT16 block_index;
	UINT16 packetsize;
	UINT8* startptr,*endptr,*ptr;
	VOID (*rx_notify)(UMUP_PCB* buffer);

  
    if (block == NULL)
	{
		return -1 ;
    }
	if(size>(buf->um_block_size-sizeof(UM_BLOCK)))
	{
		return -2;
	}
	rx_notify = NULL;

    DB_LOCK_DISABLE;
    /* get block index */
//    block_index = ((UNSIGNED)block - (UNSIGNED)buf->um_data_ptr)/buf->um_block_size;
	
	block->um_ref=0;
	block->um_length=sizeof(UMUP_BLOCK);

	startptr=(UINT8*)((UINT32)block+sizeof(UMUP_BLOCK));
	endptr=(UINT8*)(startptr+size);
	
	for(ptr=startptr;ptr<endptr;ptr+=packetsize)
	{
		packetsize=(ptr[0]<<8|ptr[1])+buf->um_packet_headersize;

		if(AC_IS_2CHIP)
		{
			packetsize=(packetsize+PACKETALLIGNSIZE-1)&PACKETALLIGNMASK;
			
			#ifdef UL_IP_DATA_OPT
			packetsize += UL_IP_DATA_LEN;
			#endif

		}
		else
		{
			if((packetsize&PACKETALLIGUNNMASK)==0)
				packetsize+=PACKETALLIGNSIZE;
			else
				packetsize=(packetsize+PACKETALLIGNSIZE-1)&PACKETALLIGNMASK;
		}

		block->um_ref++;
	}
	
	block->umup_ref= block->um_ref;
	rx_notify = buf->um_rx_notify;
	
	
	buf->um_hdr->um_block_put_index++;
	if (buf->um_hdr->um_block_put_index>= buf->um_block_num) 
		buf->um_hdr->um_block_put_index= 0;

	DB_LOCK_ENABLE;
	//log_printf("<-put block[%d] %x,ref %d\n", block_index,  (UINT32)block,block->um_ref);

    if(rx_notify!=NULL)
	{
		rx_notify(buf);
	}
	return 0;
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMUPC_Data_Buffer_Get                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function allocates memory from the specified the memory     */
/*      pool.  If the memory is currently available, this function       */
/*      is completed immediately.  Otherwise, if there is not enough     */
/*      memory currently available, task suspension is possible.         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Get             Error checking shell             */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      size                                Number of bytes to be        */
/*                                              allocated                */
/*      newblock                            whether allocates the memory */
/*                                              from a new block         */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Data Pointer                                                     */
/*                                                                       */
/*************************************************************************/

DATA_ELEMENT *UMUPC_Data_Buffer_Get(UMUP_PCB *buf, UINT16* size)
{
    DB_LOCK_INIT;
    DATA_ELEMENT* ptr=NULL;
    DATA_ELEMENT* block_ptr;
    UINT16 next_index;
    UMUP_BLOCK* block;
	UINT16 packetsize;
    ptr = NULL;
	
    DB_LOCK_DISABLE;
	if ((buf->um_hdr->um_buffer_get_index == buf->um_hdr->um_block_put_index)||
						(buf->um_block_by_application==1))
	{
		 DB_LOCK_ENABLE;
		 *size=0;
         return NULL;
	}

	next_index = buf->um_hdr->um_buffer_get_index+1;
    if (next_index >= buf->um_block_num) next_index = 0;
	
    block = UPDATABLOCK(buf, next_index);

	if(block->um_ref==0)
	{
		DB_LOCK_ENABLE;
		 *size=0;
		 //log_printf("um_ref is invalid\r\n");
		return NULL;
	}
	
	block_ptr = (DATA_ELEMENT*)block;
    ptr = &block_ptr[block->um_length];
	
	packetsize=(ptr[0]<<8|ptr[1]);
	*size=packetsize;

	packetsize=packetsize+buf->um_packet_headersize;
	
	if(AC_IS_2CHIP)
	{
		packetsize=(packetsize+PACKETALLIGNSIZE-1)&PACKETALLIGNMASK;
		
		#ifdef UL_IP_DATA_OPT
		packetsize += UL_IP_DATA_LEN;
		#endif

	}
	else
	{
		if((packetsize&PACKETALLIGUNNMASK)==0)
			packetsize+=PACKETALLIGNSIZE;
		else
			packetsize=(packetsize+PACKETALLIGNSIZE-1)&PACKETALLIGNMASK;
	}
	
    block->um_length += packetsize;

	block->um_ref--;
	if (block->um_ref==0)
	{
        buf->um_hdr->um_buffer_get_index = next_index;
    }
    DB_LOCK_ENABLE;
	//log_printf("<-get buffer 0x%x,from block[%d]=0x%x\r\n",ptr,next_index,block_ptr);
    return ptr;
}
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      UMUPC_Data_Buffer_Put_Stall                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function release the memory to the specified the memory     */
/*      pool. This means the momory was filled with data, and can be     */
/*      sent.                                                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*      UMC_Data_Buffer_Put_Stall             Error checking shell       */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      CSC_Place_On_List                   Add node to linked-list      */
/*      [HIC_Make_History_Entry]            Make entry in history log    */
/*      [TCT_Check_Stack]                   Stack checking function      */
/*      TCT_Protect                         Data structure protect       */
/*      TCT_Unprotect                       Un-protect data structure    */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      buf                                 Memory pool control buffer   */
/*                                            pointer                    */
/*      ptr                                 pointer of bytes to be       */
/*                                              released                 */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                                             */
/*                                                                       */
/*************************************************************************/

VOID UMUPC_Data_Buffer_Put(UMUP_PCB *buf, DATA_ELEMENT *ptr)
{
    DB_LOCK_INIT;
    UINT16 block_index;
    UMUP_BLOCK* block;
    VOID (*resume_notify)(UMUP_PCB* buffer);

    resume_notify = NULL;
	
	block_index = (ptr - buf->um_data_ptr)/buf->um_block_size;
    block = UPDATABLOCK(buf, block_index);
	if(block->umup_ref ==0)
	{
		//log_printf("UMUPC_Data_Buffer_Put()invalid input value\r\n");
		return;
	}
    DB_LOCK_DISABLE;
	
    block->umup_ref --;
    if (block->umup_ref == 0)
    {
    	UINT16 next_index;
		next_index=buf->um_hdr->um_buffer_put_index+1;
		if(next_index>=buf->um_block_num) next_index=0;
		
        if (block_index != next_index)
        {

			block->um_length = sizeof(UMUP_BLOCK);
			block->um_ref = 0;
        }
        else
        {

			
			while(buf->um_hdr->um_buffer_put_index!=buf->um_hdr->um_buffer_get_index)
			{
            	buf->um_hdr->um_buffer_put_index = next_index;
			
				/* move to next block */
				block->um_length = sizeof(UMUP_BLOCK);
				block->um_ref = 0;

				next_index=buf->um_hdr->um_buffer_put_index+1;
				if(next_index>=buf->um_block_num) next_index=0;

				block = UPDATABLOCK(buf, next_index);
				if(block->umup_ref != 0)
				break;
			}
			
           	if (buf->um_waiting_lwm)
    	   	{
        		UINT16 block_num;

       			block_num = buf->um_block_num + buf->um_hdr->um_buffer_put_index - buf->um_hdr->um_block_get_index;
        		block_num = block_num % buf->um_block_num;
        		if (block_num < buf->um_lwm)
        		{
            		resume_notify = buf->um_resume_notify;
            		buf->um_waiting_lwm = 0;
        		}
    		}
        }
    }
    DB_LOCK_ENABLE;
	//log_printf("<-put buffer %x,to block[%d]\r\n",ptr,block_index);
 
 	if(resume_notify!=NULL)
 	{
		resume_notify(buf);
 	}
 
}
VOID UMUPC_Data_Buffer_Block_By_App(UMUP_PCB *buf)
{
	 DB_LOCK_INIT;
	 DB_LOCK_DISABLE;

	 buf->um_block_by_application= 1;
	 
	 DB_LOCK_ENABLE;
	 //log_printf("Block_By_App\r\n");
}
VOID UMUPC_Data_Buffer_Unblock_By_App(UMUP_PCB *buf)
{
	 DB_LOCK_INIT;
	 VOID (*resume_notify)(UMUP_PCB* buffer);
	 //log_printf("Unblock_By_App\r\n");
	 DB_LOCK_DISABLE;

	 resume_notify=NULL;
	 if (buf->um_block_by_application==1)
   	 {
        		
        		buf->um_block_by_application=0;
				resume_notify = buf->um_resume_notify;
     }

	 DB_LOCK_ENABLE;
	 if(resume_notify!=NULL)
 	 {
		resume_notify(buf);
 	 }
	 
}


