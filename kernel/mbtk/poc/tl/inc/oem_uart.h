#ifndef __OEM_UART_H__
#define __OEM_UART_H__

/*
** modem AT commands
*/
extern int oem_atc_wait_modem_ready(void (*cb)(char *));
extern int oem_atc_get_rssi(void (*cb)(int rssi, int val2));
extern int oem_atc_get_operator(void (*cb)(char *ostr, int olen, int act));
extern int oem_atc_get_iccid(void (*cb)(char *obuf, int olen));

// callback parameter: 2=2G 3=3G 4=4G
extern int oem_atc_get_nw_info(void (*cb)(int xG));

// tag = "TFDK" "TGA" "ILG"
extern int oem_atc_get_hw_version(void (*cb)(char *tag));

// shutdown module
extern int oem_atc_power_down(void (*cb)(void));

/* set cfun=0 then cfun=1
** restart the modem.
*/
extern int oem_atc_restart_UE(void);

/*
** gps control interface
*/
extern void oem_atc_start_gps(void);
extern void oem_atc_stop_gps(void);

/*
** wait the modem finish init-ing codec.
*/
extern int oem_atc_wait_codec(void);

// "18/10/15,07:36:53+32"
extern int oem_atc_wallclock(char *outs);

/*
** poc mcu interface
*/
extern int joem_start_uart_man(void (*cb)(char *, int), void (*hk)(const char *, int));
extern void joem_stop_uart_man(void);
extern int joem_uart_send(const char *buffer, int length);


#endif
