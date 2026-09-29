#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secboot.h"
#include "reg.h"
#include "ptable.h"
#include "loadtable.h"
#include "fip.h"
#include "auth_common.h"
#include "tbbr_oid.h"
#include "pmic.h"
#include "nvctr_flash.h"

/* ----------------------------------- MACRO -----------------------------------*/



/* ----------------------------------- External Variable Definition --------------------------*/
uint32_t g_item_cert_id;
uint32_t flash_nv_ctr_addr;


/* ----------------------------------- Loacal Variable Definition --------------------------*/
static void *s_cookie;



/* ----------------------------------- Loacal Function Declaration --------------------------*/
static BOOL nvctr_major_enabled(void);


/* ----------------------------------- External Variable Declaration -------------------------*/

/* ----------------------------------- External Function Declaration -------------------------*/
extern void display_binary(void *data, size_t len);

/* ----------------------------------- External Function Definition --------------------------------*/

/*
 * Authenticate by Non-Volatile counter
 *
 * To protect the system against rollback, the platform includes a non-volatile
 * counter whose value can only be increased. All certificates include a counter
 * value that should not be lower than the value stored in the platform. If the
 * value is larger, the counter in the platform must be updated to the new
 * value.
 *
 * nvctr_cert: nv counters from certification
 * nvctr_plat: nv counters from platform
 *
 * Return: 0 = success, Otherwise = error
 */
int auth_anti_roolback(nvctr_t nvctr_cert, nvctr_t nvctr_plat)
{
	int rc;

	if(nvctr_major_enabled()) {
		if(nvctr_cert.s.major < nvctr_plat.s.major) {
			/* Invalid NV-counter */
			LOG_ERR("major,Invalid NV counters!\n");
			return -1;
		} else if(nvctr_cert.s.major > nvctr_plat.s.major) {
			rc = plat_set_nv_ctr(s_cookie, nvctr_cert);
#if 0
			return_if_error(rc);
#else
			if( rc != 0 ){
				LOG_ERR("major,update nv counter partition error, rc: %d\r\n",rc);
				return -2;
			}
#endif
		}
	}

	LOG_INFO("nvctr_cert.s.minor:0x%x,nvctr_plat.s.minor:0x%x\r\n",nvctr_cert.s.minor , nvctr_plat.s.minor);
	if(nvctr_cert.s.minor < nvctr_plat.s.minor) {
		/* Invalid NV-counter */
		LOG_ERR("Invalid NV counters!\n");
		return -1;
	} else if(nvctr_cert.s.minor > nvctr_plat.s.minor) {
		// note:
		// boot33 or updater can only update nv counter partition when "nvctr_cert.s.minor > nvctr_plat.s.minor"
		LOG_INFO("nv_counter_write_permission:%d\r\n",get_nv_counter_write_permission());
		if( 1 == get_nv_counter_write_permission() ){
			rc = plat_set_nv_ctr(s_cookie, nvctr_cert);
		}else{
			rc = 0;
		}
#if 0		
		return_if_error(rc);
#else
		if( rc != 0 ){
			LOG_ERR("update nv counter partition error, rc: %d\r\n",rc);
			return -2;
		}
#endif
	}

	return 0;
}

/* 
 * Description:
 *    get the nv counter from the platform ( platform is meaning to nv_counter partition )
 *
 * Return: 0 = success, Otherwise = error
 */
int auth_get_plat_nvctr(nvctr_t *nvctr_plat)
{
	int rc;

	/* Initialize the nv counter from the platform */
	rc = plat_init_nv_ctr();
	return_if_error(rc);	

	/* Get NV counter from the platform */
	rc = plat_get_nv_ctr(s_cookie, nvctr_plat);
	return_if_error(rc);
	LOG_INFO("Platform nv counter: 0x%lx\r\n", nvctr_plat->nv_ctr);

	return 0;	
}

/* 
 * Description:
 *    get the nv counter from the certification.
 *
 * Return: 0 = success, Otherwise = error
 */
int auth_get_cert_nvctr(nvctr_t *nvctr_cert)
{
	auth_param_type_desc_t nv_ctr_desc = {AUTH_PARAM_NV_CTR ,NON_TRUSTED_FW_NVCOUNTER_OID};
	char *nv_ctr_ptr = NULL;
	unsigned int nv_ctr_len;
	char *p;
	uint32_t cert_nv_ctr;
	unsigned int len, i;
	
	get_auth_param(&nv_ctr_desc,NULL,NULL,&nv_ctr_ptr,&nv_ctr_len);
	/* Parse the DER encoded integer */
	ASSERT(nv_ctr_ptr);
	p = (char *)nv_ctr_ptr;
	
#ifdef ENABLE_AUTH_NVCTR_DEBUG_LOG
	SECBOOT_DBG("auth param data: ");
	for(i = 0; i < nv_ctr_len; i++) {
	  SECBOOT_DBG("%02X ", *(p + i));
	}
	SECBOOT_DBG("\r\n");
#endif

	if(*p != ASN1_INTEGER) {
		/* Invalid ASN.1 integer */
		return_if_error(-1);
	}
	p++;
	
	/* NV-counters are unsigned integers up to 32-bit */
	len = (unsigned int)(*p & 0x7f);
	if((*p & 0x80) || (len > 4)) {
		return_if_error(-1);
	}
	p++;
	
	/* Check the number is not negative */
	if(*p & 0x80) {
		return_if_error(-1);
	}
	
	/* Convert to unsigned int. This code is for a little-endian CPU */
	cert_nv_ctr = 0;
	for(i = 0; i < len; i++) {
		cert_nv_ctr = (cert_nv_ctr << 8) | *p++;
	}
	LOG_INFO("Certification nv counter: 0x%lx\r\n",cert_nv_ctr);
	//while(1);
	
	nvctr_cert->nv_ctr = cert_nv_ctr;
#ifdef ENABLE_AUTH_NVCTR_DEBUG_LOG
	LOG_INFO("func:%s,line:%d\r\n",__func__,__LINE__);
#endif

	s_cookie = (void *)(nv_ctr_desc.cookie);	// platform add, to avoid call "get_auth_param" again in "auth_get_plat_nvctr:.
	return 0;
}

BOOL auth_arb_enable(void)
{
	struct ptentry *pt_nv;
	
	pt_nv = ptable_find_entry(NV_CTR_PART_NAME);
	
	return pt_nv == NULL ? FALSE : TRUE;
}

/* ----------------------------------- Local Function Define ----- --------------------------------*/
static BOOL nvctr_major_enabled(void)
{
	switch(GetChipID()){
		default:
		return FALSE;
	}
}

