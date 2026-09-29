
#ifndef _MBTK_ACCTIMER_H
#define _MBTK_ACCTIMER_H


typedef void(*ol_acc_timer_cb)(unsigned int);	/* Function pointer */

typedef struct mbtk_acc_timer_config					/* timer configuration */
{
	unsigned int flag;
	unsigned int period;
	ol_acc_timer_cb timer_cb;
	unsigned int timerParams;
}mbtk_acc_timer_config;


typedef enum    /* determine whether the timer is started or not*/
{
    OL_ACC_ACTIVE,                      /* the node has been added in the active_list and callback function has not been executed */
    OL_ACC_INACTIVE,                    /* the node is not in the active_list*/
    OL_ACC_TIMER_ID_NOT_EXIST           /* timer_id does not exist */                 
}MBTK_ACC_TIMER_STATUS;


int ol_acc_timer_create(mbtk_acc_timer_config *cfg);
int ol_acc_timer_delete(int acc_timer_id);
int ol_acc_timer_start(int acc_timer_id,mbtk_acc_timer_config *pTimerCfg);
int ol_acc_timer_stop(int acc_timer_id);
int ol_acc_timer_start_ex(unsigned int flag,
						  unsigned int period,
						  ol_acc_timer_cb timer_cb,
						  unsigned int timer_params
					     );
MBTK_ACC_TIMER_STATUS ol_acc_get_timer_status(int acc_timer_id);



#endif

