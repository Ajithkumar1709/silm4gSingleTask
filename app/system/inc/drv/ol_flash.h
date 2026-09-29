#ifndef _OL_FLAHS_API_H_
#define _OL_FLAHS_API_H_

#ifdef __cplusplus
extern "C" {
#endif

//page
#define FLASH_PAGE_SIZE (0x00001000)
#define FLASH_PAGE_MASK (FLASH_PAGE_SIZE-0x1)
//sector
#define FLASH_SECTOR_SIZE (0x00001000)
#define FLASH_SECTOR_MASK (FLASH_SECTOR_SIZE-0x1)
//block
#define FLASH_BLOCK_SIZE  (0x00010000)
#define FLASH_BLOCK_SIZE_MASK	(FLASH_BLOCK_SIZE -0x1)


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_norflash_do_read
 * DESCRIPTION 
 *  	This API is used to read data from nor flash
 * PARAMETERS 
 *		partion_name : system partion name
 *    src_addr : flash data start address
 *		dst_addr : buffer address
 *		size : read data length
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_norflash_do_read(unsigned char *partion_name,unsigned int src_addr,unsigned int dst_addr,unsigned int size);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_norflash_do_write
 * DESCRIPTION 
 *  	This API is used to write data to nor flash
 * PARAMETERS
 *		partion_name : system partion name
 *    addr : flash data start address
 *		buf_addr : buffer address
 *		size : write data length
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_norflash_do_write(unsigned char *patition_name, unsigned int addr, unsigned int buf_addr, unsigned int size);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_norflash_do_read
 * DESCRIPTION 
 *  	This API is used to erase flash data
 * PARAMETERS
 *		partion_name : system partion name
 *    addr : flash data start address
 *		size : read data length
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_norflash_do_erase(unsigned char *patition_name, unsigned int addr, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif