#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "nvctr_flash.h"
#include "auth_nvctr.h"
//#include "asr_nor_flash.h"
#include "tbbr_oid.h"
#include "ptable.h"
#include "secboot.h"
#include "loadtable.h"

/* ----------------------------------- Loacal Function Declaration --------------------------*/



/* ----------------------------------- Local Function Define ----- --------------------------------*/
static int flash_nv_ctr_read(uint32_t addr, void *data, size_t size)
{
    //LOG_WARN("func:%s, line:%d,addr:0x%08x,size:0x%08x\n",__func__,__LINE__,addr,size);
	//asr_norflash_read((uint32_t)addr, (uint8_t *)data, (uint32_t)size);
	if((addr & FLASH_BASE_ADDR)==FLASH_BASE_ADDR){
        addr -= FLASH_BASE_ADDR;
	}
	
	int ret=crane_qspi_read((unsigned int)addr,(unsigned int)data,(unsigned int)size);
	return ret;
}

static int flash_nv_ctr_write(uint32_t addr, const void *data, size_t size)
{
    //LOG_WARN("func:%s, line:%d,addr:0x%08x,size:0x%08x\n",__func__,__LINE__,addr,size);
	if((addr & FLASH_BASE_ADDR)==FLASH_BASE_ADDR){
        addr -= FLASH_BASE_ADDR;
	}

    int ret=crane_qspi_write((unsigned int)addr,(unsigned int)data,(unsigned int)size);
	//asr_norflash_write((uint32_t)addr,  (uint8_t *)data, (uint32_t)size);
	return ret;
}

static int flash_nv_ctr_erase(uint32_t addr, size_t size)
{
    //LOG_WARN("func:%s, line:%d,addr:0x%08x,size:0x%08x\n",__func__,__LINE__,addr,size);
	if((addr & FLASH_BASE_ADDR)==FLASH_BASE_ADDR){
        addr -= FLASH_BASE_ADDR;
	}
    
    int ret=crane_qspi_erase((unsigned int)addr,(unsigned int)size);
	//asr_norflash_erase((unsigned int)addr, (unsigned int)size);
	return ret;
}

/*
 * Description:
 *    copy primary sector content into backup sector content.
 * NV Counters layout:
   ___________________________________________________________
 | init_value | counter | swap counter| init_value | counter | swap counter|
 |_________|_______|___________|_________|_______ |___________|
 |          page 0    |   last page  |        page 0       | last page    |
 |_________________|___________|_________________ |___________|
 |        primary  sector N          |        backup  sector N+1          |
 |_____________________________|______________________________| 
 */
static int make_backup(void)
{
	flash_otp_nv_ctr_region_t primary_nv_ctr;
	size_t sz, rc;
	uint32_t swap_count_addr;

	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.init_value) + sizeof(primary_nv_ctr.nv_counters);
	if(0 != (size_t)flash_nv_ctr_read(flash_nv_ctr_addr,&primary_nv_ctr, sz)) {
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + ( NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
	if(0 != (size_t)flash_nv_ctr_read(swap_count_addr,&primary_nv_ctr.swap_count, sz)) {
		return_if_error(-1);
	}

	sz = flash_nv_ctr_erase(flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE, NV_COUNTER_SECTOR_SIZE);
	if(sz != 0) {
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.init_value) + sizeof(primary_nv_ctr.nv_counters);
	rc = flash_nv_ctr_write(flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE, &primary_nv_ctr, sz);
	if(0 != rc) {
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE + ( NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
	rc = flash_nv_ctr_write(swap_count_addr,&primary_nv_ctr.swap_count, sz);
	if(0 != rc) {
		return_if_error(-1);
	}

	return 0;
}

/*
 * Description:
 *    copy backup sector content into primary sector content.
 */
static int restore_backup(void)
{
	flash_otp_nv_ctr_region_t backup_nv_ctr;
	size_t sz, rc;
	uint32_t swap_count_addr;

	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.init_value) + sizeof(backup_nv_ctr.nv_counters);
	if(0 != (size_t)flash_nv_ctr_read(flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE,&backup_nv_ctr, sz)) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE + (NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;									 
	if(0 != (size_t)flash_nv_ctr_read(swap_count_addr, &backup_nv_ctr.swap_count, sz)) {
		return_if_error(-1);
	}

	sz = flash_nv_ctr_erase(flash_nv_ctr_addr, NV_COUNTER_SECTOR_SIZE);
	if(sz != 0) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.init_value) + sizeof(backup_nv_ctr.nv_counters);
	rc = flash_nv_ctr_write(flash_nv_ctr_addr, &backup_nv_ctr, sz);
	if(rc != 0) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + (NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
	rc = flash_nv_ctr_write(swap_count_addr,&backup_nv_ctr.swap_count, sz);
	if(rc != 0) {
		return_if_error(-1);
	}

	return 0;
}

static int create_or_restore_layout(void)
{
	flash_otp_nv_ctr_region_t primary_nv_ctr;
	flash_otp_nv_ctr_region_t backup_nv_ctr;
	size_t sz;
	int rc;
	uint32_t swap_count_addr;

	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.init_value);
	rc = flash_nv_ctr_read(flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE, &backup_nv_ctr.init_value, sz);
	if(rc != (size_t)0) {
		return_if_error(-1);
	}

	sz = sizeof(backup_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE + ( NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
	rc = flash_nv_ctr_read(swap_count_addr,&backup_nv_ctr.swap_count, sz);
	if(rc != (size_t)0) {
		return_if_error(-1);
	}

	if(backup_nv_ctr.init_value == OTP_NV_COUNTERS_INITIALIZED &&
	 backup_nv_ctr.swap_count != 0 &&
	 backup_nv_ctr.swap_count != UINT32_MAX) {    /* valid backup, restore */
	 	uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);
		uart_printf("copy bakcup into primary\r\n",__func__,__LINE__);
		rc = restore_backup();
		return_if_error(rc);
	} else {
		/* No valid layouts, create from scratch */
		uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);
		uart_printf("No valid layouts, create from scratch \r\n");
		primary_nv_ctr.init_value = OTP_NV_COUNTERS_INITIALIZED;
		primary_nv_ctr.nv_counters[CHECK_NV_CTR_INDEX].nv_ctr = 0;
		primary_nv_ctr.swap_count = 1;

		sz = flash_nv_ctr_erase(flash_nv_ctr_addr, NV_COUNTER_SECTOR_SIZE);
		if(sz != 0) {
			return_if_error(-1);
		}

		sz = sizeof(primary_nv_ctr.init_value) + sizeof(primary_nv_ctr.nv_counters);
		rc = flash_nv_ctr_write(flash_nv_ctr_addr, &primary_nv_ctr, sz);
		if(rc != (size_t)0) {
			return_if_error(-1);
		}

		sz = sizeof(primary_nv_ctr.swap_count);
		swap_count_addr = flash_nv_ctr_addr + ( NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
		rc = flash_nv_ctr_write(swap_count_addr, &primary_nv_ctr.swap_count, sz);
		if(rc != (size_t)0) {
			return_if_error(-1);
		}

		rc = make_backup();
		if( rc != 0 ){
			return_if_error(rc);
		}
	}

	return 0;
}

int plat_get_nv_ctr(void *cookie, nvctr_t *nv_ctr)
{
	const char *oid;
	size_t sz;
	flash_otp_nv_ctr_region_t primary_nv_ctr;

	ASSERT(cookie != NULL);
	ASSERT(nv_ctr != NULL);

	oid = (const char *)cookie;
	if(strcmp(oid, NON_TRUSTED_FW_NVCOUNTER_OID) != 0) {		
		uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);
		return_if_error(-1);
	}

	//uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);

	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		nv_ctr->nv_ctr = 0;
		return 0;
	}

	//uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);

	sz = sizeof(primary_nv_ctr.init_value) + sizeof(primary_nv_ctr.nv_counters);
	if(0 != (size_t)flash_nv_ctr_read(flash_nv_ctr_addr, &primary_nv_ctr, sz)) {
		return_if_error(-1);
	}
	//uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);
	*nv_ctr = primary_nv_ctr.nv_counters[CHECK_NV_CTR_INDEX];

	return 0;
}
/*---------------------------------------------------------------------------*/
int plat_set_nv_ctr(void *cookie, nvctr_t nv_ctr)
{
	const char *oid;
	flash_otp_nv_ctr_region_t primary_nv_ctr;
	size_t sz;
	int rc;
	uint32_t swap_count_addr;
	_ptentry *pt_nv;

	ASSERT(cookie != NULL);
	//ASSERT(nv_ctr != NULL);		// nv_ctr is not pointer, so no need to check parameter

	oid = (const char *)cookie;
	if(strcmp(oid, NON_TRUSTED_FW_NVCOUNTER_OID) != 0) {
		return_if_error(-1);
	}  

	pt_nv = ptable_find_entry(NV_CTR_PART_NAME);
	if(!pt_nv){
		LOG_WARN("Not found %s partition, continue...\n", NV_CTR_PART_NAME);
		return 0;
	}

	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		primary_nv_ctr.swap_count = 1;
	} else {
		sz = sizeof(primary_nv_ctr.swap_count);
		swap_count_addr = flash_nv_ctr_addr + (NV_COUNTER_PAGES_PER_SECTOR - 1 ) * NV_COUNTER_PAGE_SIZE;
		if(0 != (size_t)flash_nv_ctr_read(swap_count_addr,&primary_nv_ctr.swap_count, sz)) {
			return_if_error(-1);
		}
		primary_nv_ctr.swap_count++;
	}

	SECBOOT_DBG("Todo set nv_ctr %u\r\n", nv_ctr.nv_ctr);

	/*Reset flash_nv_ctr_addr from the new ptable. */
	flash_nv_ctr_addr = pt_nv->vstart;

	sz = flash_nv_ctr_erase(flash_nv_ctr_addr, NV_COUNTER_SECTOR_SIZE);
	if( 0 != sz ){
		return_if_error(-1);
	}

	primary_nv_ctr.init_value = OTP_NV_COUNTERS_INITIALIZED;
	primary_nv_ctr.nv_counters[CHECK_NV_CTR_INDEX] = nv_ctr;
	sz = sizeof(primary_nv_ctr.init_value) + sizeof(primary_nv_ctr.nv_counters);
	rc = flash_nv_ctr_write(flash_nv_ctr_addr, &primary_nv_ctr, sz);
	if(0 != (size_t)rc) {
		return_if_error(-1);
	}

	if(primary_nv_ctr.swap_count == 0 ||
		primary_nv_ctr.swap_count == UINT32_MAX) {
		primary_nv_ctr.swap_count = 1;
	}

	sz = sizeof(primary_nv_ctr.swap_count);
	swap_count_addr = flash_nv_ctr_addr + (NV_COUNTER_PAGES_PER_SECTOR - 1 ) * NV_COUNTER_PAGE_SIZE;
	rc = flash_nv_ctr_write(swap_count_addr, &primary_nv_ctr.swap_count, sz);
	if(0 != (size_t)rc) {
		return_if_error(-1);
	}

	rc = make_backup();
	return_if_error(rc);

	return 0;
}

/*---------------------------------------------------------------------------*/
/* NV Counters layout:
   ___________________________________________________________
 | init_value | counter | swap counter| init_value | counter | swap counter|
 |_________|_______|___________|_________|_______ |___________|
 |          page 0    |   last page  |        page 0       | last page    |
 |_________________|___________|_________________ |___________|
 |        primary  sector N          |        backup  sector N+1          |
 |_____________________________|______________________________|
 */
static int init_nv_ctr_from_partition(void)
{
	flash_otp_nv_ctr_region_t primary_nv_ctr;
	flash_otp_nv_ctr_region_t backup_nv_ctr;
	size_t sz;
	int rc;
	uint32_t swap_count_addr;

	struct ptentry *pt_nv = ptable_find_entry(NV_CTR_PART_NAME);
	if(!pt_nv) {
		LOG_WARN("Not found %s partition\r\n",NV_CTR_PART_NAME);
		flash_nv_ctr_addr = INVALID_FLASH_ADDRESS;
		return 0;
	}
	//LOG_PRINT("func:%s, line:%d\r\n",__func__,__LINE__);
	flash_nv_ctr_addr = pt_nv->vstart;
	if(flash_nv_ctr_addr == INVALID_FLASH_ADDRESS) {
		LOG_WARN("func:%s, line:%d\r\n",__func__,__LINE__);
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.init_value);
	if( 0 != (size_t)flash_nv_ctr_read(flash_nv_ctr_addr, &primary_nv_ctr.init_value, sz)){
		LOG_WARN("func:%s, line:%d\r\n",__func__,__LINE__);
		return_if_error(-1);
	}

	sz = sizeof(primary_nv_ctr.swap_count);
	/*swap count store in the last page of a sector. */
	swap_count_addr = flash_nv_ctr_addr + (NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
	if(0 != (size_t)flash_nv_ctr_read(swap_count_addr,&primary_nv_ctr.swap_count, sz)) {
		LOG_WARN("func:%s, line:%d\r\n",__func__,__LINE__);
		return_if_error(-1);
	}

	//LOG_PRINT("init_value:0x%x,swap_count:0x%x\n",primary_nv_ctr.init_value,primary_nv_ctr.swap_count);
	if(primary_nv_ctr.init_value != OTP_NV_COUNTERS_INITIALIZED ||
	(primary_nv_ctr.swap_count == 0 || primary_nv_ctr.swap_count == UINT32_MAX)) {
		//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
		rc = create_or_restore_layout();
		//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
		LOG_PRINT("rc:%d\r\n",rc);
		return_if_error(rc);
	} else {
		//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
		sz = sizeof(backup_nv_ctr.swap_count);
		swap_count_addr = flash_nv_ctr_addr + NV_COUNTER_SECTOR_SIZE + (NV_COUNTER_PAGES_PER_SECTOR - 1) * NV_COUNTER_PAGE_SIZE;
		if(0 != (size_t)flash_nv_ctr_read(swap_count_addr,&backup_nv_ctr.swap_count, sz)) {
			//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
			//LOG_PRINT("rc:%d\n",rc);
			return_if_error(-1);
		}

		if(backup_nv_ctr.swap_count == 0 ||
		backup_nv_ctr.swap_count == UINT32_MAX ||
		backup_nv_ctr.swap_count < primary_nv_ctr.swap_count ||
		(backup_nv_ctr.swap_count == UINT32_MAX - 1 && primary_nv_ctr.swap_count == 1)) {
			rc = make_backup();
			//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
			//LOG_PRINT("rc:%d\n",rc);
			return_if_error(rc);
		}
	}
	//LOG_PRINT("func:%s, line:%d\n",__func__,__LINE__);
	return 0;
}

int plat_init_nv_ctr(void)
{
	int rc;

	/* init_value and nv_counters occupation <= page size. */
	if(NV_COUNTER_PAGE_SIZE < (sizeof(flash_otp_nv_ctr_region_t) - sizeof(uint32_t))) {
		return_if_error(-1);
	}

	rc = init_nv_ctr_from_partition();
	uart_printf("func:%s,line:%d\r\n",__func__,__LINE__);
	return_if_error(rc);

	return 0;
}

#if 0
void test_erase_primary_content(void)
{
	struct ptentry *pt_nv = ptable_find_entry(NV_CTR_PART_NAME);

	if( pt_nv != NULL ){
		flash_nv_ctr_erase(pt_nv->vstart, NV_COUNTER_SECTOR_SIZE);
	}
}

void test_erase_primary_and_backup_content(void)
{
	struct ptentry *pt_nv = ptable_find_entry(NV_CTR_PART_NAME);
	
	if( pt_nv != NULL ){
		flash_nv_ctr_erase(pt_nv->vstart, 2 * NV_COUNTER_SECTOR_SIZE);
	}
}
#endif

