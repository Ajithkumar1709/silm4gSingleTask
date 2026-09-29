#ifndef __OL_SYS_H__
#define __OL_SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int TIMER_ID;

typedef void(*ol_acc_timer_cb)(UINT32);	/* Function pointer */


typedef struct mbtk_acc_timer_config					/* timer configuration */
{
	unsigned int flag;
	unsigned int period;
	ol_acc_timer_cb timer_cb;
	unsigned int timerParams;
}mbtk_acc_timer_config;

typedef enum   /* The meaning of the API flag*/         
{
	OL_ACC_TIMER_PERIODIC = 0x1,		/* periodic execution */
	OL_ACC_TIMER_AUTO_DELETE = 0x2	    /* one execution */
}MBTK_ACC_TIMER_FLAG;


typedef enum    /* determine whether the timer is started or not*/
{
    OL_ACC_ACTIVE,                      /* the node has been added in the active_list and callback function has not been executed */
    OL_ACC_INACTIVE,                    /* the node is not in the active_list*/
    OL_ACC_TIMER_ID_NOT_EXIST           /* timer_id does not exist */                 
}MBTK_ACC_TIMER_STATUS;



#define OL_ACC_TIMER_NO_MEMORY 0             /* memory is not enough*/
#define OL_ACC_TIMER_ERR_PARAMS (-1)   /* incorrect parameter*/
#define OL_ACC_TIMER_ERR_NOT_SUPPORT (-2)   /* not support*/




/*****************************************************************************
 *
 * FUNCTION 
 *		ol_acc_timer_create
 * DESCRIPTION 
 *  		acc timer create
 * PARAMETERS 
 *		cfg            [IN] timer config
 * RETURN VALUES
 *		int     >0 && <=32               TIMER_ID
 				OL_ACC_TIMER_NO_MEMORY
 				OL_ACC_TIMER_ERR_PARAMS
 				OL_ACC_TIMER_ERR_NOT_SUPPORT
 *
 *****************************************************************************/
extern int ol_acc_timer_create(mbtk_acc_timer_config *cfg);

/*****************************************************************************
 *
 * FUNCTION 
 *		ol_acc_timer_delete
 * DESCRIPTION 
 *  		delete timer
 * PARAMETERS 
 *		acc_timer_id           [IN] TIMER_ID create by  ol_acc_timer_create or  ol_acc_timer_start_ex   
 * RETURN VALUES
 *		int     >0 && <=32               TIMER_ID
 				OL_ACC_TIMER_NO_MEMORY
 				OL_ACC_TIMER_ERR_PARAMS
 				OL_ACC_TIMER_ERR_NOT_SUPPORT
 *
 *****************************************************************************/
extern int ol_acc_timer_delete(TIMER_ID acc_timer_id);

/*****************************************************************************
 *
 * FUNCTION 
 *		ol_acc_timer_start
 * DESCRIPTION 
 *  		acc timer start
 * PARAMETERS 
 *		acc_timer_id         [IN] TIMER_ID create by  ol_acc_timer_create  
 		cfg            		 [IN] timer config
 * RETURN VALUES
 *		int     >0 && <=32               TIMER_ID
 				OL_ACC_TIMER_NO_MEMORY
 				OL_ACC_TIMER_ERR_PARAMS
 				OL_ACC_TIMER_ERR_NOT_SUPPORT
 *
 *****************************************************************************/
extern int ol_acc_timer_start(TIMER_ID acc_timer_id,mbtk_acc_timer_config *cfg);

/*****************************************************************************
 *
 * FUNCTION 
 *		ol_acc_timer_stop
 * DESCRIPTION 
 *  		acc timer stop
 * PARAMETERS 
 *		acc_timer_id         [IN] TIMER_ID create by  ol_acc_timer_create   or  ol_acc_timer_start_ex   
 * RETURN VALUES
 *		int     >0 && <=32               TIMER_ID
 				OL_ACC_TIMER_NO_MEMORY
 				OL_ACC_TIMER_ERR_PARAMS
 				OL_ACC_TIMER_ERR_NOT_SUPPORT
 *
 *****************************************************************************/
extern int ol_acc_timer_stop(TIMER_ID acc_timer_id);

/*****************************************************************************
 *
 * FUNCTION 
 *		ol_acc_timer_start_ex
 * DESCRIPTION 
 *  		acc timer create and start
 * PARAMETERS 
 *		flag            		 [IN]    MBTK_ACC_TIMER_FLAG
 		period                   [IN]    period     unit is us
 		timer_cb				 [IN]    ol_acc_timer_cb  callback function
 		timer_params			 [IN]    ol_acc_timer_cb  param 
 * RETURN VALUES
 *		int     >0 && <=32               TIMER_ID
 				OL_ACC_TIMER_NO_MEMORY
 				OL_ACC_TIMER_ERR_PARAMS
 				OL_ACC_TIMER_ERR_NOT_SUPPORT
 *
 *****************************************************************************/
extern int ol_acc_timer_start_ex(unsigned int flag,
					  unsigned int period,
					  ol_acc_timer_cb timer_cb,
					  unsigned int timer_params);


/*****************************************************************************
 *
 * FUNCTION 
 *		ol_get_timer_status
 * DESCRIPTION 
 *  		acc timer status
 * PARAMETERS 
 *		acc_timer_id         [IN] TIMER_ID create by  ol_acc_timer_create   or  ol_acc_timer_start_ex   
 * RETURN VALUES
 *		int    MBTK_ACC_TIMER_STATUS
 *
 *****************************************************************************/
extern MBTK_ACC_TIMER_STATUS ol_acc_get_timer_status(TIMER_ID acc_timer_id);

#ifdef __cplusplus
}
#endif

#endif
