/******************************************************************************************************************************
*              MODULE IMPLEMENTATION FILE
******************************************************************************************************************************
*  COPYRIGHT (C) 2019 ASR Corporation.
*
*  This file and the software in it is furnished under
*  license and may only be used or copied in accordance with the terms of the
*  license. The information in this file is furnished for informational use
*  only, is subject to change without notice, and should not be construed as
*  a commitment by ASR Corporation. ASR Corporation assumes no
*  responsibility or liability for any errors or inaccuracies that may appear
*  in this document or any software that may be provided in association with
*  this document.
*  Except as permitted by such license, no part of this document may be
*  reproduced, stored in a retrieval system, or transmitted in any form or by
*  any means without the express written consent of ASR Corporation.
*
*  Title:   HTTP Package HTTP API
*
*  Filename:    http_api.h
**
*  Description: This file includes all the API that the http Package support
*
*  Last Modified: <Initial> <date>
*
*  Notes:
*********************************************************************************************************************************/
#ifndef __MBTK_HTTP_API_H__
#define __MBTK_HTTP_API_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
buffer: the buffer is received http context data
size: the length of http context data 
nitems: the http response header "Content-Length" value
private_data: user private data
*/
typedef int (*client_response_cb)(char *buffer, int size, int nitems, void *private_data);
typedef void http_client;

//#define HTTP_CLIENT_ERROR -1
//#define HTTP_CLIENT_OK     0

#define HTTPCLIENT_MEM_SIZE 2048

enum {
	HTTPCLIENT_OPT_URL,
	HTTPCLIENT_OPT_METHOD,
	HTTPCLIENT_OPT_HTTP1_0,
	HTTPCLIENT_OPT_HTTPHEADER,
	HTTPCLIENT_OPT_POSTDATA,
	HTTPCLIENT_OPT_POSTLENGTH,
	HTTPCLIENT_OPT_RESPONSECB,
	HTTPCLIENT_OPT_RESPONSECB_DATA,
  HTTPCLIENT_OPT_HEAD_RESPONSECB,
  HTTPCLIENT_OPT_HEAD_RESPONSECB_DATA,	
	HTTPCLIENT_OPT_AUTH_TYPE,
	HTTPCLIENT_OPT_AUTH_USERNAME,
	HTTPCLIENT_OPT_AUTH_PASSWORD,
	HTTPCLIENT_OPT_PDP_CID,
	HTTPCLIENT_OPT_BIND_PORT,
	HTTPCLIENT_OPT_DNS_TYPE,
	HTTPCLIENT_OPT_PROXY_ENABLE,
	HTTPCLIENT_OPT_PROXY_URL,
	HTTPCLIENT_OPT_RECV_TIMEOUT,
	HTTPCLIENT_OPT_USER_AGENT,
	HTTPCLIENT_OPT_VERIFY,
	HTTPCLIENT_OPT_CA,
	HTTPCLIENT_OPT_CLI_CRT,
	HTTPCLIENT_OPT_CLI_KEY,
	HTTPCLIENT_OPT_SSL_VSN,
};

enum {
	HTTPCLIENT_GETINFO_RESPONSE_CODE,
	HTTPCLIENT_GETINFO_TCP_STATE,
};

enum {
	HTTPCLIENT_REQUEST_GET,
	HTTPCLIENT_REQUEST_POST,
	HTTPCLIENT_REQUEST_PUT,
	HTTPCLIENT_REQUEST_HEAD,
	HTTPCLIENT_REQUEST_MAX
};

enum {
	HTTP_AUTH_TYPE_BASE = 1,
	HTTP_AUTH_TYPE_DIGEST
};

enum {
	HTTP_TCP_NOT_ESTABLISHED = 0,
	HTTP_TCP_ESTABLISHED
};

enum {
	HTTP_CLIENT_ERROR = -1,
	HTTP_CLIENT_OK = 0,
	HTTP_CLIENT_BAD_SOCKET_ID,
	HTTP_CLIENT_NO_MEMORY,
	HTTP_CLIENT_BAD_HTTP_REQUEST,
	HTTP_CLIENT_SEND_FAILED,
	HTTP_CLIENT_RECV_FAILED,
	HTTP_CLIENT_HEADER_SIZE_TOO_LARGE,
	HTTP_CLIENT_GET_INVALID_HEADER,
	HTTP_CLIENT_PROCESS_HEADER_FAILED,
	HTTP_CLIENT_CALLBACK_FAILED,
	HTTP_CLIENT_CREATE_SOCKET_FAILED,
	HTTP_CLIENT_INVALID_LOCATION,
};


struct http_client_list {
	char * data;
	struct http_client_list * next;
};
typedef void(*http_asyn_finish_cb)(int error);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_init
 * DESCRIPTION 
 *  		This API is to init http client
 * PARAMETERS 
 * RETURN VALUES
 *		NULL 	: init error
 *		http_client   :   http client
 *	
 *****************************************************************************/
extern http_client * ol_http_client_init(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_shutdown
 * DESCRIPTION 
 *  		This API is to close http connect
 * PARAMETERS 
 *		http_client[IN]               http client create by ol_http_client_init
 * RETURN VALUES
 *		void
 *	
 *****************************************************************************/
extern void ol_http_client_shutdown(http_client *);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_list_append
 * DESCRIPTION 
 *  		This API is to generate buffer string like http head. 
 * PARAMETERS 
 *		http_client_list[IN]               list link for head or other string opt
	    char[IN]                           link list one node
 * RETURN VALUES
 *		http_client_list 	:  linklist point
 *		NULL:				 error
 *	
	header = ol_http_client_list_append(header, "Content-Type: text/xml;charset=UTF-8\r\n");
	header = ol_http_client_list_append(header, "SOAPAction:\r\n");
	ol_http_client_setopt(client, HTTPCLIENT_OPT_HTTPHEADER, header);
 *****************************************************************************/
extern struct http_client_list * ol_http_client_list_append(struct http_client_list *, const char *);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_list_destroy
 * DESCRIPTION 
 *  		This API is to destory http client
 * PARAMETERS 
 *		http_client_list[IN]               list link to destory
 * RETURN VALUES
 *		void
 *	
 *****************************************************************************/
extern void ol_http_client_list_destroy(struct http_client_list *);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_setopt
 * DESCRIPTION 
 *  		This API is to set http option, option is 
	 enum {
		HTTPCLIENT_OPT_URL,
		HTTPCLIENT_OPT_METHOD,
		HTTPCLIENT_OPT_HTTP1_0,
		HTTPCLIENT_OPT_HTTPHEADER,
		HTTPCLIENT_OPT_POSTDATA,
		HTTPCLIENT_OPT_POSTLENGTH,
		HTTPCLIENT_OPT_RESPONSECB,
		HTTPCLIENT_OPT_RESPONSECB_DATA,
		HTTPCLIENT_OPT_AUTH_TYPE,
		HTTPCLIENT_OPT_AUTH_USERNAME,
		HTTPCLIENT_OPT_AUTH_PASSWORD,
		HTTPCLIENT_OPT_PDP_CID,
		HTTPCLIENT_OPT_BIND_PORT,
	};
 * PARAMETERS 
 *		http_client_list[IN]               http client
	    opt[IN]               option
	    value[IN]               value of  option
 * RETURN VALUES
 *		=0 	: set success
 *		!=0   : error
 *	
 enum {
	HTTP_CLIENT_ERROR = -1,
	HTTP_CLIENT_OK = 0,
	HTTP_CLIENT_BAD_SOCKET_ID,
	HTTP_CLIENT_NO_MEMORY,
	HTTP_CLIENT_BAD_HTTP_REQUEST,
	HTTP_CLIENT_SEND_FAILED,
	HTTP_CLIENT_RECV_FAILED,
	HTTP_CLIENT_HEADER_SIZE_TOO_LARGE,
	HTTP_CLIENT_GET_INVALID_HEADER,
	HTTP_CLIENT_PROCESS_HEADER_FAILED,
	HTTP_CLIENT_CALLBACK_FAILED,
	HTTP_CLIENT_CREATE_SOCKET_FAILED,
	HTTP_CLIENT_INVALID_LOCATION,
};
 error type

 demo:
	ol_http_client_setopt(client, HTTPCLIENT_OPT_URL, "https://www.baidu.com"); 
	ol_http_client_setopt(client, HTTPCLIENT_OPT_HTTP1_0, 0);				
	
	ol_http_client_setopt(client, HTTPCLIENT_OPT_RESPONSECB, response_cb);	
	ol_http_client_setopt(client, HTTPCLIENT_OPT_RESPONSECB_DATA, private_data);			
	ol_http_client_setopt(client, HTTPCLIENT_OPT_POSTDATA, "nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890");
	ol_http_client_setopt(client, HTTPCLIENT_OPT_POSTLENGTH, strlen("nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890nihao12345678901234567890"));
 *****************************************************************************/
extern int ol_http_client_setopt(http_client *, int, ...);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_perform
 * DESCRIPTION 
 *  		This API is to connect http server and do action,
            this function will be block until action is finished
 * PARAMETERS 
 *		http_client_list[IN]               http client
 * RETURN VALUES
  * 	 =0  : success
  * 	 !=0   : error
  *  
  enum {
	 HTTP_CLIENT_ERROR = -1,
	 HTTP_CLIENT_OK = 0,
	 HTTP_CLIENT_BAD_SOCKET_ID,
	 HTTP_CLIENT_NO_MEMORY,
	 HTTP_CLIENT_BAD_HTTP_REQUEST,
	 HTTP_CLIENT_SEND_FAILED,
	 HTTP_CLIENT_RECV_FAILED,
	 HTTP_CLIENT_HEADER_SIZE_TOO_LARGE,
	 HTTP_CLIENT_GET_INVALID_HEADER,
	 HTTP_CLIENT_PROCESS_HEADER_FAILED,
	 HTTP_CLIENT_CALLBACK_FAILED,
	 HTTP_CLIENT_CREATE_SOCKET_FAILED,
	 HTTP_CLIENT_INVALID_LOCATION,
 };
  error type
 *	
 *****************************************************************************/
extern int ol_http_client_perform(http_client *);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_perform_asyn
 * DESCRIPTION 
 *  		This API is to connect http server and do action,
            this function will be non-block
            
 * PARAMETERS 
 *		http_client_list[IN]               http client
        cb[IN]                             will be call when http action is fihish 
 * RETURN VALUES
 *		=0	: success
 *		!=0   : error
 * RETURN MESSAGE
 * 		 NONE
 *	
	demo can refer to  http_client_demo_noblock
 *****************************************************************************/
extern int ol_http_client_perform_asyn(http_client *, http_asyn_finish_cb cb);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_getinfo
 * DESCRIPTION 
 *  		This API is to get http action return info
 * PARAMETERS 
 *		http_client_list[IN]               http client
	    opt[IN]               set audio callbacke					enum {
																		 HTTPCLIENT_GETINFO_RESPONSE_CODE,
																		 HTTPCLIENT_GETINFO_TCP_STATE,
																	 };
		value[OUT]                option value
 * RETURN VALUES
 *		=0	: set success
 *		!=0   : error
 *****************************************************************************/
extern int ol_http_client_getinfo(http_client *, int, void *);

#ifdef __cplusplus
}
#endif

#endif