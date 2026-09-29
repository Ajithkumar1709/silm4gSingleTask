#ifndef SIMCOM_SIMCARD_H
#define SIMCOM_SIMCARD_H

#include "simcom_os.h"
#include "mbtk_pub_type.h"

typedef enum {
    SC_SIM_RETURN_SUCCESS,
    SC_SIM_RETURN_FAIL,
    SC_SIM_RTEURN_UNKNOW
}SC_simcard_err_e;


typedef enum {
    SC_HOTSWAP_QUERY_STATE,
    SC_HOTSWAP_QUERY_LEVEL,
    SC_HOTSWAP_SET_SWITCH,
    SC_HOTSWAP_SET_LEVEL,
    SC_HOTSWAP_QUERY_OUTSTATE,
    SC_HOTSWAP_SET_OUTSWITCH
}SC_HotSwapCmdType_e;


typedef struct {
    char spn[16];
    char mcc[16];
    char mnc[16];
}Hplmn_st;

SC_simcard_err_e sAPI_SysGetHplmn(char *HplmnValue);
SC_simcard_err_e sAPI_SysGetIccid(char *IccidValue);
SC_simcard_err_e sAPI_SimcardSwitchMsg(UINT8 status, sMsgQRef msgQ);
SC_simcard_err_e sAPI_SimcardHotSwapMsg (SC_HotSwapCmdType_e opt, UINT8 param, sMsgQRef msgQ);
SC_simcard_err_e sAPI_SimcardPinSet(char * oldpin, char * newpin, int new);
SC_simcard_err_e sAPI_SimcardPinGet(UINT8 *gcpin);
SC_simcard_err_e sAPI_SysGetImsi(char *ImsiValue);
SC_simcard_err_e sAPI_SysGetBindSim(UINT8 *bindsim);
SC_simcard_err_e sAPI_SysSetBindSim(UINT8 bindsim);
SC_simcard_err_e sAPI_SysGetDualSimType(UINT8 *type);
SC_simcard_err_e sAPI_SysSetDualSimType(UINT8 type);

#endif
