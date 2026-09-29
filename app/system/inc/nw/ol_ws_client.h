// Copyright 2015-2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _OL_WS_CLIENT_H_
#define _OL_WS_CLIENT_H_


#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "mbtk_os.h"

#ifdef __cplusplus
extern "C" {
#endif

#define portTICK_RATE_MS   5
#define portTICK_PERIOD_MS 1000



typedef void  *mbtk_websocket_client_handle_t;
typedef void   (*mbtk_event_handler_t)(int32_t event_id, void* event_data); /**< function called when an event is posted to the queue */


typedef int32_t mbtk_ws_err_t;
typedef uint32_t TickType_t;


/* Definitions for error constants. */
#define MBTK_WS_OK          0       /*!< mbtk_ws_err_t value indicating success (no error) */
#define MBTK_WS_FAIL        -1      /*!< Generic mbtk_ws_err_t code indicating failure */

#define MBTK_WS_ERR_NO_MEM              0x101   /*!< Out of memory */
#define MBTK_WS_ERR_INVALID_ARG         0x102   /*!< Invalid argument */
#define MBTK_WS_ERR_INVALID_STATE       0x103   /*!< Invalid state */
#define MBTK_WS_ERR_INVALID_SIZE        0x104   /*!< Invalid size */
#define MBTK_WS_ERR_NOT_FOUND           0x105   /*!< Requested resource not found */
#define MBTK_WS_ERR_NOT_SUPPORTED       0x106   /*!< Operation or feature not supported */
#define MBTK_WS_ERR_TIMEOUT             0x107   /*!< Operation timed out */
#define MBTK_WS_ERR_INVALID_RESPONSE    0x108   /*!< Received response was invalid */
#define MBTK_WS_ERR_INVALID_CRC         0x109   /*!< CRC or checksum was invalid */
#define MBTK_WS_ERR_INVALID_VERSION     0x10A   /*!< Version was invalid */
#define MBTK_WS_ERR_INVALID_MAC         0x10B   /*!< MAC address was invalid */

#define MBTK_WS_ERR_WIFI_BASE           0x3000  /*!< Starting number of WiFi error codes */
#define MBTK_WS_ERR_MESH_BASE           0x4000  /*!< Starting number of MESH error codes */
#define MBTK_WS_ERR_FLASH_BASE          0x6000  /*!< Starting number of flash error codes */

#define portMAX_DELAY               0xFFFFFFFF

/**
 * @brief Websocket Client events id
 */
typedef enum {
    WEBSOCKET_EVENT_ANY = -1,
    WEBSOCKET_EVENT_ERROR = 0,      /*!< This event occurs when there are any errors during execution */
    WEBSOCKET_EVENT_CONNECTED,      /*!< Once the Websocket has been connected to the server, no data exchange has been performed */
    WEBSOCKET_EVENT_DISCONNECTED,   /*!< The connection has been disconnected */
    WEBSOCKET_EVENT_DATA,           /*!< When receiving data from the server, possibly multiple portions of the packet */
	WEBSOCKET_EVENT_CLOSED,
	WEBSOCKET_EVENT_MAX
} mbtk_websocket_event_id_t;

/**
 * @brief Websocket event data
 */
typedef struct {
    char *data_ptr;                   /*!< Data pointer */
    int data_len;                           /*!< Data length */
    uint8_t op_code;                        /*!< Received opcode */
    mbtk_websocket_client_handle_t client;   /*!< mbtk_websocket_client_handle_t context */
    void *user_context;                     /*!< user_data context, from mbtk_websocket_client_config_t user_data */
    int payload_len;                        /*!< Total payload length, payloads exceeding buffer will be posted through multiple events */
    int payload_offset;                     /*!< Actual offset for the data associated with this event */
	mbtk_websocket_event_id_t event;
} mbtk_websocket_event_data_t;



typedef enum {
    WEBSOCKET_STATE_ERROR = -1,
    WEBSOCKET_STATE_UNKNOW = 0,
    WEBSOCKET_STATE_INIT,
    WEBSOCKET_STATE_CONNECTED,
    WEBSOCKET_STATE_WAIT_TIMEOUT,
    WEBSOCKET_STATE_CLOSING,
} websocket_client_state_t;


/**
 * @brief Websocket Client transport
 */
typedef enum {
    WEBSOCKET_TRANSPORT_UNKNOWN = 0x0,  /*!< Transport unknown */
    WEBSOCKET_TRANSPORT_OVER_TCP,       /*!< Transport over tcp */
    WEBSOCKET_TRANSPORT_OVER_SSL,       /*!< Transport over ssl */
} mbtk_websocket_transport_t;

/**
 * @brief Websocket client setup configuration
 */
typedef struct {
    const char                  *uri;                       /*!< Websocket URI, the information on the URI can be overrides the other fields below, if any */
                                                             //ws://192.168.1.75:30073/v1
                                                             //wss://192.168.1.75:30073/v1
    const char                  *host;                      /*!< Domain or IP as string, will be covered by uri*/
    int                         port;                       /*!< Port to connect, default depend on mbtk_websocket_transport_t (80 or 443),  
                                                               will be covered by uri*/
    const char                  *username;                  /*!< Using for Http authentication - 
	                                                           Not supported for now */
    const char                  *password;                  /*!< Using for Http authentication - 
	                                                           Not supported for now */
    const char                  *path;                      /*!< HTTP Path, if not set, default is `/` */
    bool                        disable_auto_reconnect;     /*!< Disable the automatic reconnect function when disconnected */
	bool 						disable_auto_ping;			/*!< wheather disable auto send ping when heartbeat timeout*/
	bool 						disable_auto_pong;			/*!< wheather disable auto send pong when receive ping for the other side*/
    void                        *user_context;              /*!< HTTP user data context */
    int                         task_prio;                  /*!< Websocket task priority */
    int                         task_stack;                 /*!< Websocket task stack */
    int                         buffer_size;                /*!< Websocket buffer size，RX,TX buffer default is 1024*/
    const char                  *cert_pem;                  /*!< SSL Certification, PEM format as string, if the client requires to verify server */
    mbtk_websocket_transport_t   transport;                  /*!< Websocket transport type, see `mbtk_websocket_transport_t */
	unsigned int    rconnect_timeout;//                       reconnect interval when connect is fail or disconnect, uint is ms, default is 10000ms
	unsigned int    nw_timeout;                             // net operation wait timeout,for example, read write, uint is ms, default is 10000ms
	unsigned int    ping_timeout;                           //ping interval, unit is ms, default is 10000ms
    char            *subprotocol;               /*!< Websocket subprotocol */
} mbtk_websocket_client_config_t;

/**
 * @brief      Start a Websocket session
 *             This function must be the first function to call,
 *             and it returns a mbtk_websocket_client_handle_t that you must use as input to other functions in the interface.
 *             This call MUST have a corresponding call to mbtk_websocket_client_destroy when the operation is complete.
 *
 * @param[in]  config  The configuration
 *
 * @return
 *     - `ol_ws_client_init`
 *     - NULL if any errors
 */
mbtk_websocket_client_handle_t ol_ws_client_init(const mbtk_websocket_client_config_t *config);

/**
 * @brief      Set URL for client, when performing this behavior, the options in the URL will replace the old ones
 *             Must stop the WebSocket client before set URI if the client has been connected
 *
 * @param[in]  client  The client
 * @param[in]  uri     The uri
 *
 * @return     mbtk_ws_err_t
 */
mbtk_ws_err_t ol_ws_client_set_uri(mbtk_websocket_client_handle_t client, const char *uri);

/**
 * @brief      Open the WebSocket connection
 *
 * @param[in]  client  The client
 *
 * @return     mbtk_ws_err_t
 */
mbtk_ws_err_t ol_ws_client_start(mbtk_websocket_client_handle_t client);

/**
 * @brief      Close the WebSocket connection
 *
 * @param[in]  client  The client
 *
 * @return     mbtk_ws_err_t
 */
mbtk_ws_err_t ol_ws_client_stop(mbtk_websocket_client_handle_t client);

/**
 * @brief      Destroy the WebSocket connection and free all resources.
 *             This function must be the last function to call for an session.
 *             It is the opposite of the mbtk_websocket_client_init function and must be called with the same handle as input that a mbtk_websocket_client_init call returned.
 *             This might close all connections this handle has used.
 *
 * @param[in]  client  The client
 *
 * @return     mbtk_ws_err_t
 */
mbtk_ws_err_t ol_ws_client_destroy(mbtk_websocket_client_handle_t client);

/**
 * @brief      Generic write data to the WebSocket connection; defaults to binary send
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int ol_ws_client_send(mbtk_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Write binary data to the WebSocket connection (data send with WS OPCODE=02, i.e. binary)
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int ol_ws_client_send_bin(mbtk_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);




///code 鍙傛暟鏈変互涓?
/*
 ??1000
 	1000表示正常关闭连接??
 ??1001
 	1001表示终端已经“going away”，比如服务器宕机或者浏览器跳转到其他页面??
 ??1002
 	1002表示终端由于协议错误终止了连接??
 ??1003
 	1003表示终端因为接收到了不能处理的数据类型，所以打算关闭连接（比如终端只理解text数据，但是收到了binary类型的消息）??
 ??1004
 预留??
 ??1005
 	1005是一个预留值，表示终端期望收到状态码但是没有收到，不能放在Close帧中??
 ??1006
 	预留值，用来表示连接被异常关闭（没有发送或者收到Close帧），不能放在Close帧中??
 ??1007
 	1007表示终端关闭了连接，因为发现收到的数据内容和实际的消息类型不匹配。（比如非UTF-8编码的数据放在了text消息中）
 ??1008
 	1008表示收到一个不符合规则的消息，并打算关闭连接。这是一个比较通用的状态码，当没有更合适的状态码或者希望隐藏一些具体的细节的时候可以选择使用??
 ??1009
 	1009表示收到一个比较大的不能处理的消息??
 ??1010
 	用来关闭连接，因为在握手阶段，客户端希望服务器使用多个扩展，但是服务器没有返回相应的扩展信息。客户端在发送Close帧时把希望使用的扩展列表放在/reason/（关闭原因）中。服务器不需要发送这个状态码，因为服务器可以直接执行_ Fail the WebSocket Connection _??
 ??1011
 	表示服务器遇到某些不能完成的请求??
 ??1015
 	表示不能进行TLS握手的时候发送（比如服务器的证书不能得到验证），是一个预留状态码，不能在Close帧中使用??
*/

int ol_ws_client_close_with_code(mbtk_websocket_client_handle_t client, int code, const char *data, int len, TickType_t timeout);

int ol_ws_client_close(mbtk_websocket_client_handle_t client, TickType_t timeout);

/**
 * @brief      Write textual data to the WebSocket connection (data send with WS OPCODE=01, i.e. text)
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int ol_ws_client_send_text(mbtk_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Check the WebSocket connection status
 *
 * @param[in]  client  The client handle
 *
 * @return
 *     - true
 *     - false
 */
bool ol_ws_client_is_connected(mbtk_websocket_client_handle_t client);

/**
 * @brief Register the Websocket Events
 *
 * @param client            The client handle
 * @param event             The event id
 * @param event_handler     The callback function
 * @param event_handler_arg User context
 * @return mbtk_ws_err_t
 */
mbtk_ws_err_t ol_ws_register_events(mbtk_websocket_client_handle_t client,
											mbtk_event_handler_t event_handler);


#ifdef __cplusplus
}
#endif

#endif
