/**
 * @file lv_customer_api.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "mbtk_cust_comm.h"


int stub_get_c_table_size();
int mbtk_unsupport_api( void );
extern mbtk_fun_table_c g_mbtk_fun_c_table[];

void *mbtk_find_addr_by_hash_c(unsigned int hash)
{
	int i=0; 
	int size = stub_get_c_table_size();
	char find=0;
	void *addr=mbtk_unsupport_api;
	
	for(i=0; i<size; i++)
	{
		if(g_mbtk_fun_c_table[i].fun_hash == hash)
		{
			addr = g_mbtk_fun_c_table[i].fun_ptr;
			break;
		}
	}
	
	return addr;
}



