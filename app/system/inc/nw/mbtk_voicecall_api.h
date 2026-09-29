/*************************************************************
Description:
    MBTK Open Voice Call Public API
*************************************************************/
#ifndef __MBTK_VOICECALL_API_H__
#define __MBTK_VOICECALL_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    MBTK_VC_EVT_NO_CARRIER_LOCAL,
    MBTK_VC_EVT_NO_CARRIER_REMOTE,
    MBTK_VC_EVT_RING,
    MBTK_VC_EVT_DIAL_CONNECT,
    MBTK_VC_EVT_DIAL_END,
}mbtk_vc_event_id_enum;

typedef struct
{
	char caller_id[24];
	unsigned char addr_type;
}mbtk_voicecall_info;

typedef void (*mbtk_vc_event_cb_f)(int event_id,void *msg);


/*************************************************************
    Function Declaration
*************************************************************/

/*****************************************************************************
 * FUNCTIO
 *    ol_vc_dial
 * DESCRIPTION
 *    This API is used for dialing
 *
 * PARAMETERS
 *    dial_digits    : [IN] dial digits 
 * RETURN VALUES
 * other: fail
 *    0: success
 *
 *****************************************************************************/
extern int ol_vc_dial(char *dial_digits);

/*****************************************************************************
 * FUNCTIO
 *  ol_vc_answer
 * DESCRIPTION
 *  This API is used for answering
 *
 * PARAMETERS
 *  NULL
 * RETURN VALUES
 * other: fail
 *    0: success
 *
 *****************************************************************************/
extern int ol_vc_answer(void);

/*****************************************************************************
 * FUNCTIO
 *  ol_vc_hangup
 * DESCRIPTION
 *  This API is used for hangup
 *
 * PARAMETERS
 *  NULL
 * RETURN VALUES
 * other: fail
 *    0: success
 *
 *****************************************************************************/
extern int ol_vc_hangup(void);

/*****************************************************************************
 * FUNCTIO
 *  ol_vc_event_register
 * DESCRIPTION
 *  This API is used to register voice call event callback
 *
 * PARAMETERS
 *  cb_func    : [IN] voice call event callback 
 * RETURN VALUES
 * other: fail
 *    0: success
 *
 *****************************************************************************/
extern int ol_vc_event_register(mbtk_vc_event_cb_f cb_func);

#ifdef __cplusplus
}
#endif

#endif /*__MBTK_VOICECALL_API_H__*/

