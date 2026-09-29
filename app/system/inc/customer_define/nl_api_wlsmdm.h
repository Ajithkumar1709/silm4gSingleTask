#ifndef _NL_API_WLSMDM_H_
#define _NL_API_WLSMDM_H_

#if 1 //just for compile
typedef struct{ 
	uint32_t tac; 
	uint32_t cell_id;
}lte_scell_info_t;

typedef struct{ 
	uint32_t lac; 
	uint32_t cell_id;
}gsm_scell_info_t;

typedef struct ip_addr ip4_addr_t;
#endif


typedef enum
{
    CFW_SIM_0 = 0x00,
    CFW_SIM_1 = 0x01,
    CFW_SIM_END = 0xFF,
    CFW_SIM_ENUM_FILL = 0x7FFFFFFF
} CFW_SIM_ID;

typedef struct
{
    uint8_t curr_rat;
	uint8_t nStatus;
	lte_scell_info_t lte_scell_info;
	gsm_scell_info_t gsm_scell_info;
	
}reg_info_t;

typedef struct{
  union {
    ip6_addr_t ip6;
    ip4_addr_t ip4;
  } u_addr;
}nl_ip_addr_t;
/**
 * @brief    获取指定已激活那路的 PDP address,支持多路PDP
 *
 * @param <cid>: 指定已激活的PDP profile ID；
 * @param <ip>输出已激活CID 的IP地址，外部建议定义长度为50；
 * @param <cid_status>:输出当前CID激活状态，0表示未激活，1表示激活
 * @param < nSimID >:sim卡subid，取值0和1，单卡用户默认为0；双卡用户取data 业务所在SIM 卡的 subid；
 * 
 * @return  返回0且IP不为0表示已经激活，否则未激活
 */
INT32 nl_PDPStatus(INT8 cid, UINT8 *ip, UINT8 *cid_status,CFW_SIM_ID nSimID);

/**
 * @brief    断开nl_PDPActive接口建立的那路PDP 连接,即默认断开CID1路
 *
 * @param < deactive >:去激活PDP ，只能取值0;
 * @param < nSimID >:sim卡subid，取值0和1，单卡用户默认为0；双卡用户取data 业务所在SIM 卡的 subid;
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_PDPRelease(UINT8 deactive, CFW_SIM_ID nSimID);


/**
 * @brief    设置initial pdp  context，仅仅支持特殊SIM卡时调用，注册时要上报APN 和鉴权参数
 *
 * @param < set_delete >:取值0和1，0 ：表示清除 initial PDP context，1：表示设置initial PDP context；
 * @param < pdptype >：IP 类型，取值1---3；1：IPV4 only，2：IPV6 ony，3：IPV4V6;
 * @param <apn>:apn 字符串
 * @param < nAuthProt > 取值，0：apn 鉴权参数无效，1：PAP，2：CHAP
 * @param <username>用户名（没有为空）；
 * @param <password>密码（没有为空）；
 * @param < nSimID >：sim卡subid，取值0和1，单卡用户默认为0；双卡用户取data 业务所在SIM 卡的 subid;
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_set_initial_pdp(INT8 set_delete, uint8_t pdptype, char *apn, uint8_t nAuthProt,char *username,char *pwd,CFW_SIM_ID nSim);

/**
 * @brief    激活PDP连接
 *
 * @param < active> PDP 激活，只能取值1；
 * @param <apn> init attach apn,可以为空，不支持设置有效数据；
 * @param <ip>输出IP地址字符串，可以是IPV4 only 或IPV6 only 或，IPV4V6 双栈地址字符串，该参数不支持；
 * @param < nAuthProt > 取值，0：apn 鉴权参数无效，1：PAP，2：CHAP 该参数不支持；
 * @param <username>用户名（没有为空），该参数不支持；
 * @param <password>密码（没有为空）；
 * @param <password>密码（没有为空）；该参数不支持
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_PDPActive(UINT8 active, UINT8 *apn, UINT8 *username, UINT8 *password, UINT8 nAuthProt, CFW_SIM_ID nSimID, UINT8 *ip);

/**
 * @brief    向模块发送AT命令，必须要等待命令返回后才能发送另一条命令。接收数据的最大长度为2048个字节。
 *
 * @param <cmd>AT命令串（包含回车0x0d）
 * @param <len>字符串长度
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_at_send(const UINT8 *cmd, UINT16 len);

/**
 * @brief    获取模组CSQ信号强度等信息
 *
 * @param <rssi>: received signal strength indication
 * @param <ber>: bit error rate
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_get_csq(INT32* rssi, INT32* ber);

/**
 * @brief    设置模块最小功能模式
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_cfun_zero(void);

/**
 * @brief    设置模块最全功能模式
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_cfun_one(void);

/**
 * @brief    获取模块注册信息
 *
 * @param <reg_info>：curr_rat：当前注册RAT,nStatus:当前注册状态，0 表示未注册,1表示注册上,GSM 服务小区参数：LAC和 cell id，,LTE 服务小区参数,TAC 和cell id；
 * @param < nSimID >：sim卡subid，取值0和1，单卡用户默认为0;双卡用户取data 业务所在SIM 卡的 subid。
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_getRegInfo(reg_info_t *reg_info,CFW_SIM_ID nSimID);

/**
 * @brief    初始化sim卡
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_find_sim(void);

/**
 * @brief    在网络上获取相应域名对应的IP，域名长度不能超过100字节。阻塞函数。
 *
 * @param <hostname>主机域名字符串
 * @param <Addr>：输出 IP 地址，输出IPV4: addr->u_addr.ip4.addr。输出IPV6：addr->u_addr.ip6.addr
 * @param <nCid> :取值1-7，默认使用1即可；
 * @param < nSimID >：sim卡subid，取值0和1，单卡用户默认为0；双卡用户取data 业务所在SIM 卡的 subid;
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_getHostByName(char *hostname,nl_ip_addr_t *addr,uint8_t nCid, CFW_SIM_ID nSimID);

/**
 * @brief    获取ccid号
 *
 * @param < ccid >: 不能为NULL 
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_get_ccid(uint8_t *ccid);

/**
 * @brief    获取模块的IMEI号
 *
 * @param <imei>: 不能为NULL ，输出IMEI，IMEI长度15；
 * @param < nSimID >：sim卡subid，取值0和1，单卡用户默认为0;双卡用户取data 业务所在SIM 卡的 subid;
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_get_imei(UINT8 *imei, CFW_SIM_ID nSimID);
INT32 nl_get_imsi(UINT8 *imsi, CFW_SIM_ID nSimID);
/**
 * @brief    获取sim卡插拔状态
 *
 * @param < pucSimStatus >:指针类型，作为出参使用，其指向内容为1时代表已插卡，0代表未插卡
 * 
 * @return  0 - 成功    ＜0 - 失败
 */
INT32 nl_get_sim_status(uint8_t *pucSimStatus);

#endif