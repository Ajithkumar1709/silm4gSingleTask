#include "simcom_network.h"
#include "ol_nw_pub.h"
#include "ol_nw_api.h"
#include "mbtk_err.h"

void sAPI_NetworkInit(void)
{
    simcom_api_not_support();
}

unsigned int sAPI_NetworkGetCsq(UINT8 *pCsq)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCreg(int *pReg)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgreg(int *pGreg)
{
    ol_REG_STATUS_INFO reg_info = {0};
    
    if(ol_nw_get_reg_status(&reg_info, OL_NW_GSM_MODE) != 0)
    {
        return SC_NET_FAIL;
    }
    
    *pGreg = reg_info.state;
    
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCpsi(SCcpsiParm *pStr)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCnmp(int *pCnmp)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCnmp(int CnmpValue)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCops(char *pCops)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCops(int modeVal,int formatVal,char *networkOperator,int accTchVal)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgdcont(SCApnParm *pCgdcont)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCgdcont(int primCid,char *type,char *APNstr)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgact(SCAPNact * pCgact)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCgact(int pdpState,int cid)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgatt(int* pCgatt)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}
unsigned int sAPI_NetworkSetCgatt(int CgattValue)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCfun(UINT8 *pCfun)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCfun(int CfunValue)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgauth(SCCGAUTHParm *pCgauth,int cid)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkSetCgauth(SCCGAUTHParm *pCgauth,BOOL delflag)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCgpaddr(int Cid,SCcgpaddrParm *Pstr)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}

unsigned int sAPI_NetworkGetCnetci(SCcnetciParm *pStr)
{
    simcom_api_not_support();
    return SC_NET_SUCCESS;
}



