#ifndef __OEM_IWALKIE_TYPE_H__
#define __OEM_IWALKIE_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define BRD_NAME_LEN   64
#define USER_OFFLINE   0
#define USER_ONLINE    1

#define MEMBER_OFFLINE 2
#define MEMBER_ONLINE  1
#define MEMBER_GROUP_ONLINE 3

typedef enum BND_CUSTOM_TYPE{
    ACCOUNT_LOGIN_ENABLE,
    WRITE_CUSTOM_ACCOUNT,
    QUERY_ALL_GROUP_MEMBER,
}BND_CUSTOM_TYPE, NOTION_CUSTOM_TYPE;

typedef enum BND_ERROR_TYPE{
    LOGIN_FAIL_4_NO_ACTIVE_NETWORK,               //无网络连接
    LOGIN_FAIL_4_USER_NOT_EXIST,                  //设备不存在
    LOGIN_FAIL_4_PASSWORD_ERROR,                  //密码错误
    LOGIN_FAIL_4_REMOTE_KILLED,                   //设备被遥毙
    LOGIN_FAIL_4_DEVICE_DISABLED,                 //设备被禁用
    LOGIN_FAIL_4_UNKNOWN,                         //登录错误
    CALLING_START_FAIL_4_TARGET_NOT_ONLINE,       //无在线设备
    CALLING_START_FAIL_4_GROUP_UPDATING,          //正在切换群组
    CALLING_START_FAIL_4_CALL_MODE_ERROR,         //呼叫模式错误
    CALLING_START_FAIL_4_PRIORITY_LOW,            //优先级低
    CALLING_START_FAIL_4_NOT_PERMIT_CALLING,      //设备被遥晕
    CALLING_START_FAIL_4_GROUP_ID_ERROR,          //呼叫群组错误
    CALLING_START_FAIL_4_TARGET_ON_CALLING,       //被叫正忙
    CALLING_START_FAIL_4_TARGET_NOT_EXIST,        //被叫不存在
    CALLING_START_FAIL_4_NOT_SUPPORT_FULL_CALL,   //不支持全呼
    CALLING_START_FAIL_4_NO_ACTIVE_NETWORK,       //无网络连接
    CALLING_START_FAIL_4_UNKNOWN,                 //呼叫失败
    CHANGE_GROUP_FAIL_4_NOT_CONFIG,               //未配置群组
    CHANGE_GROUP_FAIL_4_TIMEOUT                   //切换群组超时
}BND_ERROR_TYPE, NOTION_ERROR_TYPE;

typedef unsigned int bnd_gid_t;

typedef unsigned int bnd_uid_t;

typedef unsigned char boolean;

typedef enum BRD_GROUP_TYPE {
    GRP_COMMON,
    GRP_SINGLECALL
}BRD_GROUP_TYPE, NOTION_GROUP_TYPE;

typedef struct bnd_group_t {
    bnd_gid_t    gid;
    char         name[BRD_NAME_LEN];
    BRD_GROUP_TYPE type;
    int          index;
}bnd_group_t;

typedef struct bnd_member_t {
    bnd_uid_t  uid;
    char       name[BRD_NAME_LEN];
    int        state; //0-在线 1-离线 3-在线在组
    unsigned int prior; 
    int    index;
}bnd_member_t;

typedef struct bnd_time_t {
    unsigned short year;
    unsigned char  month;
    unsigned char  day;
    unsigned char  hour;
    unsigned char  minute;
    unsigned char  second;
    unsigned short millisecond;
}bnd_time_t;

typedef struct bnd_dispatch_notice_t{
    unsigned int uid;                  //调度通知发送人id，如果是调度账号，发送id为0
    char         name[BRD_NAME_LEN];  //调度通知发送人名称，如果是调度账号，发送名称为空
    char         content[256];           //调度通知内容，为utf-8编码
}bnd_dispatch_notice_t;

typedef struct bnd_sos_alarm_t{
    unsigned int uid;                   //sos告警发起人id
    char         name[BRD_NAME_LEN];    //sos告警发起人名称
    unsigned int gid;                        //sos告警发起人所在群组id
    char         group_name[BRD_NAME_LEN];   //sos告警发起人所在群组名称
    unsigned long long time;                 //sos发起时间，unix时间戳，64bit长度
}bnd_sos_alarm_t;

typedef enum
{
    //BND_PARA_MIN,
    BND_PARA_OPEN,
    BND_PARA_ACCOUNTFIRST,
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
    char str[16];
    bnd_para_enum at_type;
    int para_num;
}mbtk_bnd_at_struct;

#define PARA_TYPE_MAX BND_PARA_MAX

typedef enum
{
    MBTK_TTS_NONE,
    MBTK_TTS_PLAY,
    MBTK_TTS_STOP
}mbtk_tts_status;

typedef void(*mbtk_tts_status_cb)(int type);


typedef struct mbtk_tts_info
{
    unsigned char play_status;
    mbtk_tts_status_cb status_cb;
}mbtk_tts_info;

#ifdef __cplusplus
}
#endif

#endif