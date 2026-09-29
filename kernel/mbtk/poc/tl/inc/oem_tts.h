#ifndef __OEM_TTS_H__
#define __OEM_TTS_H__

typedef enum {
    OEM_TTS_EV_INIT,
    OEM_TTS_EV_DEINIT,

    OEM_TTS_EV_START,
    OEM_TTS_EV_DATA,
    OEM_TTS_EV_INTERRUPT,
    OEM_TTS_EV_FINISH,
    OEM_TTS_EV_FAILED
} OEM_TTS_event_t;

extern int  OEM_TTS_init(void (*cb)(int, char*, int));
extern void OEM_TTS_deinit(void);

extern void OEM_TTS_play(int type, const char *str, int slen);
extern void OEM_TTS_stop(void);

extern void OEM_TTS_set_volume(int level, int max_l);

extern void OEM_TTS_check_tts_service(void);

#endif
