#ifndef _MBTK_CUST_AT_CMDS_H_
#define _MBTK_CUST_AT_CMDS_H_
#include <utlAtParser.h>
#include "mat.h"
#include "stub.h"

#include "mbtk_atcommands.h"
typedef enum
{
	MBTK_CUST_CMD_TYPE_START = MBTK_CMD_TYPE_END,
	MBTK_CUST_CMD_TEST,
	MBTK_CMD_POC,
	MPOC_SET_PARAM_POC,
	MAT_IND_POCCFG,
	MBTK_CUST_CMD_FACTORY,
	MBTK_CUST_CMD_PYTHON,
	MBTK_CUST_CMD_CAT_FS,
}MBTK_CUST_AT_CMD_TYPE;


utlAtCommand_T *mbtk_get_cust_atcommands_table(void);
unsigned int mbtk_get_cust_atcommands_num(void);

#endif
