#include "simcom_os.h"
#include "simcom_common.h"

int sAPI_UrcRefRegister(sMsgQRef ref, UINT32 mask)
{
    if(mask & SC_URC_GNSS_MASK)
    {
        extern sMsgQRef gGpsUrcMsgQueue;
        gGpsUrcMsgQueue = ref;
    }
    if(mask & SC_URC_INTERNAL_AT_RESP_MASK)
    {
        extern sMsgQRef gAtUrcMsgQueue;
        gAtUrcMsgQueue = ref;
    }
    return 0;
}

