// Copyright (c) Mobiletek. All rights reserved.
// 

#ifndef OL_ENV_H
#define OL_ENV_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
extern "C"
{
#else
#include <stddef.h>
#include <stdint.h>
#endif


#define ENV_TIMEZONE		"TIMEZONE"
#define ENV_UART_LOG		"UART_LOG"
#define ENV_NITZ_EN			"NITZ_EN"
#define ENV_SDIO_TYPE		"SDIO_TYPE"

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_getenv
 * DESCRIPTION 
 *  	This API is used to get environment variable
 * PARAMETERS 
 *		env_name : environment variable name
 * RETURN VALUES
 *		a string type environment variable vaule
 *		NULL will return if error or environment variable vaule if not exist
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
char* ol_getenv(unsigned char *env_name);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_setenv
 * DESCRIPTION 
 *  	This API is used to set environment variable
 * PARAMETERS 
 *		env_name : environment variable name
 *    env_value : environment variable value
 *		value_len : the string length of param env_value
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
int ol_setenv(unsigned char *env_name,unsigned char *env_value,unsigned char value_len);

#ifdef __cplusplus
}
#endif

#endif /* OL_ENV_H */


