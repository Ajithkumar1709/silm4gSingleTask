#ifndef _MBTK_AT_CMDS_H_
#define _MBTK_AT_CMDS_H_
#include <utlAtParser.h>

typedef enum
{
	MBTK_CMD_TYPE_START = NUM_OF_MAT_CMD,
	MBTK_CMD_TEST,
	#ifdef MBTK_FOTA_SUPPORT
	MBTK_CMD_FOTA,	
	#endif
	MSET_SCAN_KEY,
	MSET_LOG_ENABLE,
#ifdef MBTK_FAC_GUI_TEST 
	MFAC_GUI_TEST,
#endif
#ifdef MBTK_FAC_TEST
	MFAC_EGCMD,
#endif
	MDUMNP_CMD_ENABLE,
#ifdef MBTK_TTS_SUPPORT
    MBTK_AT_TTS_PLAY,
#endif
	MBTK_IND_GTPOS,
	MBTK_CMD_MINIFOTA,
	// TODO:add at commands...	
	MBTK_CMD_TYPE_END
}MBTK_AT_CMD_TYPE;


utlAtCommand_T *mbtk_get_atcommands_table(void);
unsigned int mbtk_get_atcommands_num(void);

#endif
