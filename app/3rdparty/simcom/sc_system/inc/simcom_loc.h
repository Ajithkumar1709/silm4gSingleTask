#ifndef _SIMCOM_LOC_H_
#define _SIMCOM_LOC_H_

#include "simcom_os.h"

typedef enum {
    SC_LBS_GET_LONLAT = 1,//获取经纬度
    SC_LBS_GET_DETAILADDRESS = 2,//获取详细地址
    SC_LBS_GET_ERRNO = 3,//获取错误码
    SC_LBS_GET_LONLATTIME = 4,//获取经纬度+时间
    SC_LBS_TEST,
    SC_LBS_DEMO_MAX
}SC_lbs_type_e;


typedef enum {
    SC_LBS_SUCCESS, //成功
    SC_LBS_FAIL, //失败
    SC_LBS_INVALID_PARAMETER, //无效参数
    SC_LBS_SIMCARD_NOT_READY, //没有 sim 卡
    SC_LBS_RESULT_NETWORK_ERROR, //网络异常
    SC_LBS_GET_LOC_FAIL, //获取定位失败
    SC_LBS_ERROR_END
}SC_lbs_err_e;


typedef struct {
    int u8ErrorCode;
    int u32Lng;
    int u32Lat;
    int u16Acc;
    int u32AddrLen;
    int u8LocAddress[16];
    int u8DateAndTime;
}SC_lbs_info_t;

typedef SC_lbs_err_e SC_LBS_RETURNCODE;

SC_LBS_RETURNCODE sAPI_LocTypeSet(int LocType);
SC_LBS_RETURNCODE sAPI_LocServerSet(char *server);
SC_LBS_RETURNCODE sAPI_LocGet(int channel, sMsgQRef magQ_urc,int type);


#endif
