#include <stdio.h>
#include <string.h>
#include "oem_tts.h"
#include "OS_Wrapper.h"
#include "jptt_debug.h"

#include "osa.h"

static void (*on_tts_event)(int, char *, int) = NULL;

/*
**
*/

void lib_oem_tts_status_cb(int ev) {
    DEBUG_I("tts ev: %d", ev);
    if (on_tts_event == NULL)
        return;

    switch (ev) {
        case 1:
            on_tts_event(OEM_TTS_EV_START, NULL, 0);
            break;
        case 0:
            on_tts_event(OEM_TTS_EV_FINISH, NULL, 0);
            break;
        default:
            on_tts_event(OEM_TTS_EV_FAILED, NULL, 0);
            break;
    }
}

// return 0:enable tts; -1:block tts
extern int OEM_TTS_init(void (*cb)(int, char *, int)) {
    on_tts_event = cb;

/*    if (on_tts_event != NULL)
        on_tts_event(OEM_TTS_EV_INIT, NULL, 0);
    */
    return -1;
}

extern void OEM_TTS_play(int type, const char *str, int slen) {
    /*DEBUG_I("tts play %s, %d", str, slen);
    lib_oem_tts_play((char *)str);*/
}

extern void OEM_TTS_stop() {
    /*DEBUG_I("stop tts playing");
    lib_oem_tts_stop();*/
}

extern void OEM_TTS_deinit() {
    //on_tts_event(OEM_TTS_EV_DEINIT, NULL, 0);
}

/*
**
*/

extern void OEM_TTS_set_volume(int level, int max_l) {
    // TODO...
}

/*
**
*/

/* check if tts service is alive.
** return 0: normal
*/
extern void OEM_TTS_check_tts_service(void) {
}

