#ifndef __MBTK_PMU_H
#define __MBTK_PMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"
#include "stdbool.h"



typedef enum
{
    /// Normal cause, ie onkey power up
    OL_POWER_CAUSE_NORMAL, 
    /// The power up was caused by charger insert
    OL_POWER_CAUSE_CHARGER,
    /// The power up was caused by ExtOn low, triggered by the usb
    OL_POWER_CAUSE_EXTON,
	/// The power up caused by alarm, from the calendar.
	OL_POWER_CAUSE_ALARM = 4,
    /// The POWER was watch dog,long_onkey
    OL_POWER_CAUSE_FAULT,
     /// The power up was caused by battery insert
    OL_POWER_CAUSE_BATTERY,
    OL_POWER_CAUSE_RESV,
    /// The power up was caused by HW reset
    OL_POWER_CAUSE_RESET_HW,
    /// The power up was caused by SW reset
    OL_POWER_CAUSE_RESET_SW,
} ol_power_reason;

typedef enum
{
    /// Starting state before the charger detection has occured once
    BATT_CHARGER_UNKNOWN,            // 0
    /// No Charger is plugged
    BATT_CHARGER_UNPLUGGED,          // 1
    /// Charger is plugged, but charge is not running
    BATT_CHARGER_PLUGGED,            // 2
    /// Charger is plugged, charge in precharge phase (whe souldn't be on anyway)
    BATT_CHARGER_PRECHARGE,          // 3
    /// Charger is plugged, charge in fast mode (constant current)
    BATT_CHARGER_FAST_CHARGE,        // 4
    /// Charger is plugged, charge in pulsed mode (constant voltage, active)
    BATT_CHARGER_PULSED_CHARGE,      // 5
    /// Charger is plugged, charge in pulsed mode (constant voltage, inactive)
    BATT_CHARGER_PULSED_CHARGE_WAIT, // 6
    /// Charger is plugged, charge done.
    BATT_CHARGER_FULL_CHARGE,        // 7
    /// Charger is plugged, charge stopped for safety (error).
    BATT_CHARGER_ERROR,              // 8
    /// Charger is plugged, charge stopped for safety (timeout).
    BATT_CHARGER_TIMED_OUT,          // 9
    /// Charger is plugged, charge stopped for safety (temperature).
    BATT_CHARGER_TEMPERATURE_ERROR,  // 10
    /// Charger is plugged, charge stopped for safety (voltage).
    BATT_CHARGER_VOLTAGE_ERROR,      // 11

    BATT_CHARGER_STATUS_QTY
} mbtk_battery_status;

typedef enum
{
	MBTK_SLEEP_DISABLE, // disable sleep
	MBTK_SLEEP_IDLE_ENABLE,   //can entry c1 sleep mode
	MBTK_SLEEP_ENABLE,       //can entry d2 sleep mode
	MBTK_SLEEP_MAX = 0xFF
}MBTK_SLEEP_STATUS;


typedef void (*mbtk_sys_event_cb)(int type);
typedef void (*pwk_callback)(void);
typedef void (*mbtk_usb_detect_callback)(int status);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_power_reset
 * DESCRIPTION 
 *  	This API is used to power reset module 
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_power_reset(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_power_down
 * DESCRIPTION 
 *  	This API is used to power off module 
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_power_down(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_sys_event_cb
 * DESCRIPTION 
 *  	This API is used to set system callback
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_set_sys_event_cb(mbtk_sys_event_cb cb);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_powerup_get_reason
 * DESCRIPTION 
 *  	This API is used to get power up reason
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_powerup_get_reason(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_battery_level
 * DESCRIPTION 
 *  	This API is used to get battery level
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint16_t ol_get_battery_vol(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_battery_percent
 * DESCRIPTION 
 *  	This API is used to get battery percent
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint8_t ol_get_battery_percent(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_battery_status
 * DESCRIPTION 
 *  	This API is used to get battery status
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_battery_status ol_get_battery_status(void);	

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_pwrkey_status
 * DESCRIPTION 
 *  	This API is used to get power key status
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_pwrkey_status(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pwrkey_register_irq
 * DESCRIPTION 
 *  	This API is used to set power key irq callback
        this call back is run at hirq
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_pwrkey_register_irq(pwk_callback callback);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pwrkey_intc_enable
 * DESCRIPTION 
 *  	This API is used to enable powkey irq
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_pwrkey_intc_enable(unsigned char mode);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_usbdect_register_cb
 * DESCRIPTION 
 *  	This API is used to detect usb status
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_usbdect_register_cb(mbtk_usb_detect_callback callback);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_is_usb_insert
 * DESCRIPTION 
 *  	This API is used to detect usb status
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int8_t ol_is_usb_insert(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_syssleep_status
 * DESCRIPTION 
 *  	This API is used to make device entry sleep or not
 * PARAMETERS 
 *      status     MBTK_SLEEP_STATUS
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_set_syssleep_status(MBTK_SLEEP_STATUS status);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_syssleep_status
 * DESCRIPTION 
 *  	This API is used to get device entry sleep or not
 * PARAMETERS 
 *		NONE
 * RETURN VALUES
 *		sleep status
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_syssleep_status(void);



#ifdef __cplusplus
}
#endif

#endif // #ifdef __MBTK_PMU_H
