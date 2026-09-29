#include "simcom_simcard.h"
#include "mbtk_sim_api.h"
#include "mbtk_err.h"


SC_simcard_err_e sAPI_SysGetHplmn(char *HplmnValue)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysGetIccid(char *IccidValue)
{
    mbtk_sim_api_err_enum rec;
    
    rec = ol_get_sim_iccid(IccidValue);

    if(rec != mbtk_sim_api_err_none)
        return SC_SIM_RETURN_FAIL;
    
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SimcardSwitchMsg(UINT8 status, sMsgQRef msgQ)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SimcardHotSwapMsg (SC_HotSwapCmdType_e opt, UINT8 param, sMsgQRef msgQ)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SimcardPinSet(char * oldpin, char * newpin, int new)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SimcardPinGet(UINT8 *gcpin)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysGetImsi(char *ImsiValue)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysGetBindSim(UINT8 *bindsim)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysSetBindSim(UINT8 bindsim)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysGetDualSimType(UINT8 *type)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}

SC_simcard_err_e sAPI_SysSetDualSimType(UINT8 type)
{
    simcom_api_not_support();
    return SC_SIM_RETURN_SUCCESS;
}


