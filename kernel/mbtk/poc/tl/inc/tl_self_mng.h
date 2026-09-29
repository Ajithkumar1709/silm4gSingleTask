#ifndef __TL_SELF_MNG__
#define __TL_SELF_MNG__

#define MAX_ACCOUNT_LEN (41)
#define MAX_SN_LEN (41)
#define MAX_IND_URL_LEN (201)

enum {
    S_OK,        // 正常
    S_UNBOUND,   // SN未绑定
    S_EXPIRED,   // 账号过期
    S_BLOCKED,   // 账号禁用     
    S_NET_ERR    // 网络错误
};

/***********************************************************
 查询SN的绑定情况
   参数： SN 为终端唯一序列码
   返回： 
     S_OK     ： 成功
     S_UNBOUND： 未查询到绑定（此时可以调用jemcu_do_accout_polling）
     S_EXPIRED： 账号过期 （无需调用jemcu_do_accout_polling）
     S_BLCOKED： 账号禁用（无需调用jemcu_do_accout_polling）     
     S_NET_ERR： 网络错误 (UI可以选择再次尝试或通知用户)
***********************************************************/
int jemcu_check_binding_status(char* SN);

/***********************************************************
 SN未绑定，轮询服务器，尝试获取途聆账号
    在 jemcu_check_binding_status 函数返回 S_UNBOUND 时，调用本函数。
   本函数会阻塞调用线程，直到超时（最大 2分钟）或者 查询到绑定账号
   参数： SN 为终端唯一序列码
   返回： 
     S_OK     ： 成功
     S_UNBOUND： 未查询到绑定，(UI可以选择再次尝试或通知用户)    
     S_NET_ERR： 网络错误 (UI可以选择再次尝试或通知用户)
***********************************************************/     
int jemcu_do_accout_polling(char* SN);

/***********************************************************
 获取查询到的途聆账号
   在 jemcu_check_binding_status 或者 jemcu_do_accout_polling返回 S_OK 时，
   调用本函数获取途聆账号
   返回： 
     途聆账号
***********************************************************/          
char* jemcu_get_tl_account(void);

/***********************************************************
 获取指示URL
   在 jemcu_check_binding_status 返回 S_EXPIRED 或者 
   jemcu_do_accout_polling 返回 S_UNBOUND 时
   调用本函数获取指示URL
   返回： 
     指示URL(扫码绑定 或 充值付费)
***********************************************************/
char* jemcu_get_ind_url(void);

#endif
