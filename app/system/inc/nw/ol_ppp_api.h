#ifndef __OL_PPP_API_H__
#define __OL_PPP_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	ppp_io_by_app,	
	ppp_io_by_uart,
}ol_ppp_io_dir;

typedef enum{
	ppp_status_disconnect,
	ppp_status_connected,
}ol_ppp_status;

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ppp_device_config
 * DESCRIPTION 
 *          This API is use to config ppp device. 
 * PARAMETERS 
 *        input    [IN]: input
 *        output   [IN]: output
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ppp_device_config(char input,char output);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ppp_start_call
 * DESCRIPTION 
 *          This API is use to start ppp call. 
 * PARAMETERS 
 *        dial_string    [IN]: dial_string
 *        cid            [IN]: cid
 *        status_cb      [IN]: status_cb
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ppp_start_call(char *dial_string,char cid,void (*status_cb)(int));

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ppp_stop_call
 * DESCRIPTION 
 *          This API is use to stop ppp call. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ppp_stop_call(void);

#ifdef __cplusplus
}
#endif

#endif
