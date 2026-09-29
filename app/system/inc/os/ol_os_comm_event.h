#ifndef __OL_OS_COMM_EVENT_H
#define __OL_OS_COMM_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	OL_EVENT_START = 0,
	//1~30 reserved

	//31~99

	//100~ for customer
	OL_EVENT_AT_RESP = 100,

	OL_EVENT_END,
}OL_OS_COMM_EVENT;

#ifdef __cplusplus
}
#endif

#endif