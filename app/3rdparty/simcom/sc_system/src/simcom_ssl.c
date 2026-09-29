#ifdef FEATURE_SIMCOM_MSSL

#include "mbtk_pub_type.h"
#include "simcom_ssl.h"

INT32 sAPI_SslHandShake(SCSslCtx_t *ctx)
{
    return 0;
}
INT32 sAPI_SslRead(UINT32 ClientID,INT8 *buf, INT32 len)
{
    return 0;
}
INT32 sAPI_SslSend(UINT32 ClientID,INT8 *buf, INT32 len)
{
    return 0;
}
void sAPI_SslClose(UINT32 ClientID)
{
    return ;
}

#endif
