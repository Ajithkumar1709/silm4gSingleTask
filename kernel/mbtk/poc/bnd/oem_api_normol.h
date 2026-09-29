#ifndef __OEM_API_NORMOL_H__
#define __OEM_API_NORMOL_H__


#define PARA_TYPE_MAX             26
#define ATCI_RESULT_CODE_ERROR    2

#if defined(MBTK_POC_SUPPORT_BND) ||  defined(MBTK_POC_SUPPORT_TL)

#ifndef MBTK_POC_SUPPORT_TL

typedef enum
{
    //BND_PARA_MIN,
    BND_PARA_OPEN,
    BND_PARA_SETACCOUNNT,
    BND_PARA_GETACCOUNNT,
    BND_PARA_LOGIN,
    BND_PARA_LOGOUT,
    BND_PARA_ENTERGROUP,
    BND_PARA_SINGLECALL,
    BND_PARA_PTT,
    BND_PARA_GROUPS,
    BND_PARA_MEMBERS,
    BND_PARA_LOC,
    BND_PARA_GROUPNUM,
    BND_PARA_MEMBERNUM,
    BND_PARA_SETNOTIFY,
    BND_PARA_LOCATIME,
    BND_PARA_SETPING,
    BND_PARA_PING,
    BND_PARA_TTSLANG,
    BND_PARA_CURRENTUSER,
    BND_PARA_TONEVOL,
    BND_PARA_TONEOPEN,
    BND_PARA_EXPIRED,
    BND_PARA_UPGRADE,
    BND_PARA_AUTOLEAVETIME,
    BND_PARA_LEAVETEMPCALL,
    BND_PARA_CALLUSER,
    BND_PARA_MAX
}bnd_para_enum;


typedef struct{
    char str[10];
    bnd_para_enum at_type;
    int para_num;
}mbtk_bnd_at_struct;

#define PARA_TYPE_MAX 26

#endif

typedef enum
{
    MBTK_TTS_NONE,
    MBTK_TTS_PLAY,
    MBTK_TTS_STOP
}mbtk_tts_status;

typedef void(*mbtk_tts_status_cb)(int type);


typedef struct mbtk_tts_info
{
    uint8 play_status;
    mbtk_tts_status_cb status_cb;
}mbtk_tts_info;


#endif /*MBTK_POC_SUPPORT_BND*/
#endif /*__OEM_API_NORMOL_H__*/

