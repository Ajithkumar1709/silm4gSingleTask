



#include "utlTime.h"



void mbtk_set_default_time()
{

	#if 0
	struct timeval current;
	if (gettimeofday(&current, NULL))
			RTI_LOG("Could not get local time of day");
	
	if(current.tv_sec <0)
	{
		//设置默认值为2022/1/1/0:0:0
		#define JAN_2022_1_1 1640995200.0
		struct tm *ltm = NULL;
		time_t timet = JAN_2022_1_1;

		ltm = localtime(&timet);
		SaveNTPParameters(ltm);
	}

	#endif
}/*******************************************************************************
 * Copyright (c) mbtk Corp.
 *
 *******************************************************************************/


