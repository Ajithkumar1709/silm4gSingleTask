#ifndef _AUTH_NVCTR_FLASH_H_
#define _AUTH_NVCTR_FLASH_H_
#include <stdint.h>
#include "auth_nvctr.h"
/*---------------------------------------------------------------------------*/
int plat_init_nv_ctr(void);
int plat_get_nv_ctr(void *cookie, nvctr_t *nv_ctr);
int plat_set_nv_ctr(void *cookie, nvctr_t nv_ctr);
#if 0
void test_erase_primary_content(void);
void test_erase_primary_and_backup_content(void);
#endif

#endif

