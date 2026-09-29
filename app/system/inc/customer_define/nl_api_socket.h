#ifndef _NL_API_SOCKET_H_
#define _NL_API_SOCKET_H_

#if 1 //just for compile
#define FD_SETSIZE				  64
#define NFDSHIFT					8
typedef	long	fd_mask;

#endif

typedef struct
{
    UINT16 sin_port; //save as network sequence
    struct ip_addr sin_addr;
} GAPP_TCPIP_ADDR_T;

typedef struct {
    fd_mask fds_bits [FD_SETSIZE >> NFDSHIFT];
}fd_set;

struct timeval {
    time_t      tv_sec;
    long tv_usec;
};

/**
 * @brief    创建一个socket，支持IPV6；
 *
 * @param < domain >: AF_INET(值2)，表示IPV4;AF_INET6(值10)，表示IPV6;
 * @param < type >: SOCK_STREAM(值1，表示TCP);SOCK_DGRAM(值2，表示UDP)
 * @param < protocol >: IPPROTO_IP(值0 表示IP)
 * 
 * @return  < 0 失败  ≥0 - 成功
 */
INT32 nl_sock_create_ex(int domain, int type, int protocol);

/**
 * @brief    与远端socket建立链接
 *
 * @param <sock>Socket id
 * @param <addr>网络字节序的地址信息；
 * 
 * @return  < 0 失败  ≥0 - 成功
 */
INT32 nl_sock_connect(INT32 sock, GAPP_TCPIP_ADDR_T *addr);

/**
 * @brief    TCP发送数据
 *
 * @param <sock>Socket id
 * @param <buff>数据首地址
 * @param <len>数据长度
 * 
 * @return  < 0 失败  ≥0 - 成功
 */
INT32 nl_sock_send(INT32 sock, UINT8 *buff, UINT16 len);

/**
 * @brief    接收TCP数据函数
 *
 * @param <sock>Socket id
 * @param <buff>接收数据buff首地址
 * @param <len>数据长度
 * 
 * @return  ≥0 - 实际接收到的数据长度(对端正常断开为0)    <0 - socket 错误（网络异常断开-1）
 */
INT32 nl_sock_recv(INT32 sock, UINT8 *buff, UINT16 len);

/**
 * @brief    关闭一个已经打开的socket
 *
 * @param <sock>Socket id
 * 
 * @return  < 0 失败  0 - 成功
 */
INT32 nl_sock_close(INT32 sock);

/**
 * @brief    获取socket选项参数
 *
 * @param <sock>Socket id
 * @param <level>协议层级(固定为0xfff)
 * @param <optname>设置选项类型，目前支持SO_KEEPALIVE
 * @param <optval>选项值指针
 * @param <optlen>选项值长度
 * 
 * @return  < 0 失败  0 - 成功
 */
INT32 nl_sock_getOpt(INT32 sock, INT32 level, INT32 optname, void *optval, INT32 *optlen);

/**
 * @brief    时时监控当前socket状态，返回当前socket的错误码
 *
 * @return  返回当前socket的错误码
 */
INT32 nl_get_socket_error(void);

/**
 * @brief    Lwip select 接口用于同一线程内多 sockets 业务 并行收发管理
 *
 * @param <maxfdp1>：管理当前创建的socket 个数，等于sockid +1，每次创建一个 sockid后sockid+1 等于该值，目前平台支持24 路socket ，亦可直接填写上 24，建议最好动态管理。
 * @param <Readset>： 检测接收数据的 参数
 * @param <Writeset>：检测发出数据的参数
 * @param <Exceptset>：记录 sockets 创建后TCP握手收发数据遇到的 error
 * @param <Timeout> 设置select 阻塞时间，给予底层充足的时间检测设置fd_set,一般设置1—5秒
 * 
 * @return  >=0 表示成功   < 0 表示失败
 */
INT32  nl_sock_lwip_select(int maxfdp1, ol_fd_set *readset, ol_fd_set *writeset, ol_fd_set *exceptset,struct timeval *timeout);

/**
 * @brief    设置首选网络模式
 *
 * @param <s>:sock_id
 * @param <cmd>:取值如下：3(F_GETFL)获取socket阻塞状态  4(F_SETFL)设置socket阻塞状态；
 * @param <val>:取值：0x4000(_FNONBLOCK)	 non blocking I/O (POSIX style) 
 * @param < nPreferRat >:取值0：LTE 优先  2：GSM only  4：LTE only
 * @param < nSimID >：sim卡subid，取值0和1，单卡用户默认为0；双卡用户取data 业务所在SIM 卡的 subid;
 * 
 * @return  >=0 表示成功   < 0 表示失败
 */
INT32  nl_sock_lwip_fcntl(int s, int cmd, int val);

#endif
