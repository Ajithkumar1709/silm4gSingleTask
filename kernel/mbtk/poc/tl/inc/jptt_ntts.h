#ifndef __JPTT_N_TTS_H__
#define __JPTT_N_TTS_H__

typedef struct {
    int used;
    int length;
    char *buffer;
} ntts_data_t;

typedef struct {
    char  ip_a[16];
    unsigned short ip_p;
    ntts_data_t *txt;
    void (*on_result)(int res, ntts_data_t *idat, ntts_data_t *rdat);
} ntts_parameters_in_t;

enum {
    TTS_Request = 111,
    TTS_Response,
    TTS_Failed
};

extern void set_service_ip(int type, char *addr, int port);

extern int ntts_find_wave(const char *buf, int len);
extern int ntts_get_wave(int fnNo, char *obuf, int *olen);

#ifndef COMPILER_ARMCC
extern int japp_check_update(char *hw_tag, int *ver, char *mbuf);
extern int japp_get_update(char *hw_tag, char *exp_md5);
#endif

#endif
