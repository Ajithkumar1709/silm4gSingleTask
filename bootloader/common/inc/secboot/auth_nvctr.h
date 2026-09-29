#ifndef __AUTH_NVCTR_H__
#define __AUTH_NVCTR_H__
#include "common.h"
#include "tbbr_img_def.h"


/* ----------------------------------- MACRO -----------------------------------*/
#define ASN1_INTEGER		(0x02)
#define ENABLE_AUTH_NVCTR_DEBUG_LOG

#define LOG_PRINT uart_printf
#define LOG_INFO  uart_printf
#define LOG_WARN  uart_printf
#define	LOG_ERR   uart_printf

#define OTP_NV_COUNTERS_INITIALIZED   0xC0DE8112U
#define UINT32_MAX					  (0xFFFFFFFF)
#define INVALID_FLASH_ADDRESS         UINT32_MAX
#define NOR_FLASH_PAGE_SIZE			  (	0x100 )
#define NOR_FLASH_SECTOR_SIZE		  ( 0x1000 )
#define NAND_FLASH_PAGE_SIZE		  ( 0x800 )
#define NAND_FLASH_SECTOR_SIZE		  ( 0x20000 )
#define NV_COUNTER_PAGE_SIZE		  (NOR_FLASH_PAGE_SIZE )
#define NV_COUNTER_SECTOR_SIZE		  (NOR_FLASH_SECTOR_SIZE )
#define NV_COUNTER_PAGES_PER_SECTOR	  (NV_COUNTER_SECTOR_SIZE / NV_COUNTER_PAGE_SIZE  )
#define NV_CTR_PART_NAME			  ("nv_counter")

#define TEMP_MAX_NUMBER_IDS_TO_SAVE_MEMORY	(2)

#define return_if_error(rc) \
	do{ \
		if(rc != 0) { \
			return rc; \
		} \
	}while(0)


/* ----------------------------------- New Struct ---------------------------------*/
typedef union __attribute__((packed, aligned(1))) {
	struct{
		uint32_t minor : 24;	/* bit[23:0], flash based nv counters */
		uint32_t major : 8; 	/* bit[31:24], fuse based nv counters */
	}s;
	uint32_t nv_ctr;
} nvctr_t;

/*
 * note:
 *     sizeof(flash_otp_nv_ctr_region_t) - sizeof(uint32_t)
 *       refer to : plat_init_nv_ctr in nvctr_flash.c (common\src)
 */
typedef struct __attribute__((packed, aligned(1))) flash_otp_nv_ctr_region {
  /* Must be the first item */
  uint32_t init_value;
#if 0  
  nvctr_t nv_counters[MAX_NUMBER_IDS + 1];
#else
  nvctr_t nv_counters[TEMP_MAX_NUMBER_IDS_TO_SAVE_MEMORY + 1];
#endif
  /* Must be last item, so that it can be written separately after the main
   * write operation has succeeded
   */
  uint32_t swap_count;
} flash_otp_nv_ctr_region_t;

/* ----------------------------------- External Variable Declaration -------------------------*/
extern uint32_t g_item_cert_id;
#define CHECK_NV_CTR_INDEX	(g_item_cert_id)
extern uint32_t flash_nv_ctr_addr;

/* ----------------------------------- External Function Declaration -------------------------*/
int auth_anti_roolback(nvctr_t nvctr_cert, nvctr_t nvctr_plat);
int auth_get_plat_nvctr(nvctr_t *nvctr_plat);
int auth_get_cert_nvctr(nvctr_t *nvctr_cert);
BOOL auth_arb_enable(void);

#endif /* __AUTH_NVCTR_H__ */

