#ifndef __JPTT_HW_H__
#define __JPTT_HW_H__

/*
** sample_rate=8K, length=320
** write & read are blocking w & r
*/
extern void hw_init_codec(int samp_rate, void (*earph_cb)(int));
extern void hw_deinit_codec(void);

extern void hw_tone_gen(int type);

extern int hw_open_player(int sample_rate, int *period_B);
extern int hw_write_player(unsigned char *buffer, int length);
extern void hw_close_player(void);

extern int hw_open_recorder(int sample_rate, int *period_B);
extern int hw_read_recorder(unsigned char *buffer, int length);
extern void hw_close_recorder(void);

/* 
** on/off = 0/0 ; return 0 means OK
** if there is no audio mixer, just return 0;
*/
extern int hw_route_player(int on);
extern int hw_route_recorder(int on);

extern int hw_get_battery(void (*cb)(int v, int charge));

// type: player=0, micphone=3
extern void hw_set_default_volume(int type, int level, int max_l);
extern void hw_config_DRC(void);
extern void hw_config_ALC(void);
extern int hw_write_5616eq(unsigned short * prs, int count);

/*
** wake-lock
*/
extern int hw_wakelock_init(void);
extern void hw_wakelock_deinit(void);
// return 0 = OK
extern int hw_wakelock_lock(void);
extern int hw_wakelock_unlock(void);

#endif
