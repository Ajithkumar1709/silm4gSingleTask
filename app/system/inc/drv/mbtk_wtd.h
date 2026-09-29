#ifndef __MBTK_WTD_H
#define __MBTK_WTD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	MBTK_WTD_OK = 1,

    MBTK_WTD_NO_HANDLER_REGISTERED = -100,
    MBTK_WTD_NULL_POINTER,
	MBTK_WTD_INTC_ERROR,
	MBTK_WTD_BAD_MATCH_VALUE
}MBTK_WTD_ERRCODE;


typedef enum
{
	MBTK_WTD_INTERRUPT_MODE = 0,
	MBTK_WTD_RESET_MODE
}MBTK_WTD_MODE;



typedef struct
{
	UINT32 matchValue;	     // Number of milliseconds from kick until reset/interrupt is generated
    MBTK_WTD_MODE mode;      // Reset or Interrupt
}MBTK_WTD_CONFIG;

typedef struct
{
	UINT32 timeTillMatch;	// current counter value
}MBTK_WTD_STATUS;


typedef enum
{
    MBTK_WTD_STOP,
    MBTK_WTD_RUNNING,
    MBTK_WTD_EXPIRED,
}MBTK_WTD_RUNSTATE;



typedef void (*mbtk_wtd_handler)(void);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_kick
 * DESCRIPTION 
 *  		This API is to kick wtd
 * PARAMETERS 
 *		void
 * RETURN VALUES
 *			void
 *
 *****************************************************************************/
extern void ol_wtd_kick(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_deactive
 * DESCRIPTION 
 *  		This API is to deactive wtd
 * PARAMETERS 
 *		void
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_deactive(void);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_active
 * DESCRIPTION 
 *  		This API is to active wtd
 * PARAMETERS 
 *		void
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_active(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_get_config
 * DESCRIPTION 
 *  		This API is to get wtd config
 * PARAMETERS 
 *		config				[OUT]  MBTK_WTD_CONFIG
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_get_config(MBTK_WTD_CONFIG *config);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_set_config
 * DESCRIPTION 
 *  		This API is to get wtd config
 * PARAMETERS 
 *		config		 		 [IN] MBTK_WTD_CONFIG
                            matchValue value can be 0-0xFFFF
                            if matchValue is 0, will auto change to 1     
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_set_config(MBTK_WTD_CONFIG *config);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_int_register
 * DESCRIPTION 
 *  		This API is to set interrupt handler 
 * PARAMETERS 
 *		hdl          [IN]  will be call when wtd timeout, only useful when ol_wtd_set_config
 					       mode is MBTK_WTD_INTERRUPT_MODE
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_int_register(mbtk_wtd_handler *hdl);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_get_status
 * DESCRIPTION 
 *  		This API is to get wtd status
 * PARAMETERS 
 *		status          [OUT]  MBTK_WTD_STATUS, if wtd is active, timeTillMatch is time left for timeout
                               ONLY can be use when mode is MBTK_WTD_RESET_MODE
 * RETURN VALUES
 *			MBTK_WTD_ERRCODE
 *
 *****************************************************************************/
extern MBTK_WTD_ERRCODE ol_wtd_get_status(MBTK_WTD_STATUS *status);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_get_run_status
 * DESCRIPTION 
 *  		This API is to get wtd run state
 * PARAMETERS 
 			void
 * RETURN VALUES
 *			MBTK_WTD_RUNSTATE
 *
 *****************************************************************************/
extern MBTK_WTD_RUNSTATE ol_wtd_get_run_status(void );



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_wtd_protect
 * DESCRIPTION 
 *  		This API is to set wtd protect, if this set true, active, deactive, config, will no use
 * PARAMETERS 
 *		prot          [IN]  1 or 0
 * RETURN VALUES
 *		bool:   protect value last time set
 *
 *****************************************************************************/
extern bool ol_wtd_protect(bool prot);

#ifdef __cplusplus
}
#endif

#endif

