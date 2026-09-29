
#ifndef _MBTK_SSL_HAL_H
#define _MBTK_SSL_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SSL Error codes
 */
#define MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE               -0x7080  /**< The requested feature is not available. */
#define MBEDTLS_ERR_SSL_BAD_INPUT_DATA                    -0x7100  /**< Bad input parameters to function. */
#define MBEDTLS_ERR_SSL_INVALID_MAC                       -0x7180  /**< Verification of the message MAC failed. */
#define MBEDTLS_ERR_SSL_INVALID_RECORD                    -0x7200  /**< An invalid SSL record was received. */
#define MBEDTLS_ERR_SSL_CONN_EOF                          -0x7280  /**< The connection indicated an EOF. */
#define MBEDTLS_ERR_SSL_UNKNOWN_CIPHER                    -0x7300  /**< An unknown cipher was received. */
#define MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN                  -0x7380  /**< The server has no ciphersuites in common with the client. */
#define MBEDTLS_ERR_SSL_NO_RNG                            -0x7400  /**< No RNG was provided to the SSL module. */
#define MBEDTLS_ERR_SSL_NO_CLIENT_CERTIFICATE             -0x7480  /**< No client certification received from the client, but required by the authentication mode. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_TOO_LARGE             -0x7500  /**< Our own certificate(s) is/are too large to send in an SSL message. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_REQUIRED              -0x7580  /**< The own certificate is not set, but needed by the server. */
#define MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED              -0x7600  /**< The own private key or pre-shared key is not set, but needed. */
#define MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED                 -0x7680  /**< No CA Chain is set, but required to operate. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE                -0x7700  /**< An unexpected message was received from our peer. */
#define MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE               -0x7780  /**< A fatal alert message was received from our peer. */
#define MBEDTLS_ERR_SSL_PEER_VERIFY_FAILED                -0x7800  /**< Verification of our peer failed. */
#define MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY                 -0x7880  /**< The peer notified us that the connection is going to be closed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO               -0x7900  /**< Processing of the ClientHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO               -0x7980  /**< Processing of the ServerHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE                -0x7A00  /**< Processing of the Certificate handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST        -0x7A80  /**< Processing of the CertificateRequest handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE        -0x7B00  /**< Processing of the ServerKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE          -0x7B80  /**< Processing of the ServerHelloDone handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE        -0x7C00  /**< Processing of the ClientKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP     -0x7C80  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Read Public. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS     -0x7D00  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Calculate Secret. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY         -0x7D80  /**< Processing of the CertificateVerify handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC         -0x7E00  /**< Processing of the ChangeCipherSpec handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_FINISHED                   -0x7E80  /**< Processing of the Finished handshake message failed. */
#define MBEDTLS_ERR_SSL_ALLOC_FAILED                      -0x7F00  /**< Memory allocation failed */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FAILED                   -0x7F80  /**< Hardware acceleration function returned with error */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH              -0x6F80  /**< Hardware acceleration function skipped / left alone data */
#define MBEDTLS_ERR_SSL_COMPRESSION_FAILED                -0x6F00  /**< Processing of the compression / decompression failed */
#define MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION           -0x6E80  /**< Handshake protocol not within min/max boundaries */
#define MBEDTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET         -0x6E00  /**< Processing of the NewSessionTicket handshake message failed. */
#define MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED            -0x6D80  /**< Session ticket has expired. */
#define MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH                  -0x6D00  /**< Public key type mismatch (eg, asked for RSA key exchange and presented EC key) */
#define MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY                  -0x6C80  /**< Unknown identity received (eg, PSK identity) */
#define MBEDTLS_ERR_SSL_INTERNAL_ERROR                    -0x6C00  /**< Internal error (eg, unexpected failure in lower-level module) */
#define MBEDTLS_ERR_SSL_COUNTER_WRAPPING                  -0x6B80  /**< A counter would wrap (eg, too many messages exchanged). */
#define MBEDTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO       -0x6B00  /**< Unexpected message at ServerHello in renegotiation. */
#define MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED             -0x6A80  /**< DTLS client must retry for hello verification */
#define MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL                  -0x6A00  /**< A buffer is too small to receive or write a message */
#define MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE             -0x6980  /**< None of the common ciphersuites is usable (eg, no suitable certificate, see debug messages). */
#define MBEDTLS_ERR_SSL_WANT_READ                         -0x6900  /**< No data of requested type currently available on underlying transport. */
#define MBEDTLS_ERR_SSL_WANT_WRITE                        -0x6880  /**< Connection requires a write call. */
#define MBEDTLS_ERR_SSL_TIMEOUT                           -0x6800  /**< The operation timed out. */
#define MBEDTLS_ERR_SSL_CLIENT_RECONNECT                  -0x6780  /**< The client initiated a reconnect from the same port. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_RECORD                 -0x6700  /**< Record header looks valid but is not expected. */
#define MBEDTLS_ERR_SSL_NON_FATAL                         -0x6680  /**< The alert message received indicates a non-fatal error. */
#define MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH               -0x6600  /**< Couldn't set the hash for verifying CertificateVerify */
#define MBEDTLS_ERR_SSL_CONTINUE_PROCESSING               -0x6580  /**< Internal-only message signaling that further message-processing should be done */
#define MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS                 -0x6500  /**< The asynchronous operation is not completed yet. */
#define MBEDTLS_ERR_SSL_EARLY_MESSAGE                     -0x6480  /**< Internal-only message signaling that a message arrived early. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_CID                    -0x6000  /**< An encrypted DTLS-frame with an unexpected CID was received. */
#define MBEDTLS_ERR_SSL_CRYPTO_IN_PROGRESS                -0x7000  /**< A cryptographic operation is in progress. Try again later. */


#define TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA 			 					0xC016
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA  								0xC039
#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA  								0xC033
#define TLS_DH_anon_WITH_AES_128_CBC_SHA  								0xC034
#define TLS_RSA_WITH_AES_256_CBC_SHA      								0xC035
#define TLS_RSA_WITH_AES_128_CBC_SHA      								0xC02F
#define TLS_RSA_WITH_NULL_MD5             								0xC001
#define TLS_RSA_WITH_NULL_SHA             								0xC002
#define TLS_PSK_WITH_AES_256_CBC_SHA      								0xC08d
#define TLS_PSK_WITH_AES_128_CBC_SHA256   								0xC0ae
#define TLS_PSK_WITH_AES_256_CBC_SHA384   								0xC0af
#define TLS_PSK_WITH_AES_128_CBC_SHA      								0xC08c
#define TLS_PSK_WITH_NULL_SHA256          								0xC0b0
#define TLS_PSK_WITH_NULL_SHA384          								0xC0b1
#define TLS_PSK_WITH_NULL_SHA             								0xC02c
#define SSL_RSA_WITH_RC4_128_SHA          								0xC005
#define SSL_RSA_WITH_RC4_128_MD5          								0xC004
#define SSL_RSA_WITH_3DES_EDE_CBC_SHA     								0xC00A

/* ECC suites, first byte is 0xC0 (ECC_BYTE) */
#define TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA     						0xC014
#define TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA     						0xC013
#define TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA   						0xC00A
#define TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA   						0xC009
#define TLS_ECDHE_RSA_WITH_RC4_128_SHA         						0xC011
#define TLS_ECDHE_ECDSA_WITH_RC4_128_SHA      						0xC007
#define TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA    						0xC012
#define TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA  						0xC008
#define TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256  						0xC027
#define TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256						0xC023
#define TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384  						0xC028
#define TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384						0xC024
#define TLS_ECDHE_ECDSA_WITH_NULL_SHA          						0xC006
#define TLS_ECDHE_PSK_WITH_NULL_SHA256        						0xC03a
#define TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256  						0xC037

/* static ECDH, first byte is 0xC0 (ECC_BYTE) */
#define TLS_ECDH_RSA_WITH_AES_256_CBC_SHA      						0xC00F
#define TLS_ECDH_RSA_WITH_AES_128_CBC_SHA      						0xC00E
#define TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA    						0xC005
#define TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA    						0xC004
#define TLS_ECDH_RSA_WITH_RC4_128_SHA          						0xC00C
#define TLS_ECDH_ECDSA_WITH_RC4_128_SHA        						0xC002
#define TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA     						0xC00D
#define TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA   						0xC003
#define TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256   						0xC029
#define TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 						0xC025
#define TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384   						0xC02A
#define TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 						0xC026

/* SHA256 */
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 							0x006b
#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 							0x0067
#define TLS_RSA_WITH_AES_256_CBC_SHA256     							0x003d
#define TLS_RSA_WITH_AES_128_CBC_SHA256     							0x003c
#define TLS_RSA_WITH_NULL_SHA256            							0x003b
#define TLS_DHE_PSK_WITH_AES_128_CBC_SHA256								0x00b2
#define TLS_DHE_PSK_WITH_NULL_SHA256        							0x00b4

/* SHA384 */
#define TLS_DHE_PSK_WITH_AES_256_CBC_SHA384 							0x00b3
#define TLS_DHE_PSK_WITH_NULL_SHA384        							0x00b5

/* AES-GCM */
#define TLS_RSA_WITH_AES_128_GCM_SHA256      							0x009c
#define TLS_RSA_WITH_AES_256_GCM_SHA384      							0x009d
#define TLS_DHE_RSA_WITH_AES_128_GCM_SHA256  							0x009e
#define TLS_DHE_RSA_WITH_AES_256_GCM_SHA384  							0x009f
#define TLS_DH_anon_WITH_AES_256_GCM_SHA384  							0x00a7
#define TLS_PSK_WITH_AES_128_GCM_SHA256      							0x00a8
#define TLS_PSK_WITH_AES_256_GCM_SHA384     							0x00a9
#define TLS_DHE_PSK_WITH_AES_128_GCM_SHA256  							0x00aa
#define TLS_DHE_PSK_WITH_AES_256_GCM_SHA384  							0x00ab

/* ECC AES-GCM, first byte is 0xC0 (ECC_BYTE) */
#define TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 					0xC02b
#define TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 					0xC02c
#define TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256  					0xC02d
#define TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384  					0xC02e
#define TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256   					0xC02f
#define TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384   					0xC030
#define TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256    					0xC031
#define TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384    					0xC032

/* AES-CCM, first byte is 0xC0 but isn't ECC,
* also, in some of the other AES-CCM suites
* there will be second byte number conflicts
* with non-ECC AES-GCM */
#define TLS_RSA_WITH_AES_128_CCM_8         								0xC0a0
#define TLS_RSA_WITH_AES_256_CCM_8        								0xC0a1
#define TLS_ECDHE_ECDSA_WITH_AES_128_CCM   								0xC0ac
#define TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8 								0xC0ae
#define TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8 								0xC0af
#define TLS_PSK_WITH_AES_128_CCM           								0xC0a4
#define TLS_PSK_WITH_AES_256_CCM           								0xC0a5
#define TLS_PSK_WITH_AES_128_CCM_8         								0xC0a8
#define TLS_PSK_WITH_AES_256_CCM_8         								0xC0a9
#define TLS_DHE_PSK_WITH_AES_128_CCM       								0xC0a6
#define TLS_DHE_PSK_WITH_AES_256_CCM       								0xC0a7

/* Camellia */
#define TLS_RSA_WITH_CAMELLIA_128_CBC_SHA        					0x0041
#define TLS_RSA_WITH_CAMELLIA_256_CBC_SHA        					0x0084
#define TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256     					0x00ba
#define TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256     					0x00c0
#define TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA    					0x0045
#define TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA    					0x0088
#define TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256 					0x00be
#define TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256 					0x00c4

/* chacha20-poly1305 suites first byte is 0xCC (CHACHA_BYTE) */
#define TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256   				0xCCa8
#define TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 				0xCCa9
#define TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256      				0xCCaa
#define TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256    				0xCCac
#define TLS_PSK_WITH_CHACHA20_POLY1305_SHA256          				0xCCab
#define TLS_DHE_PSK_WITH_CHACHA20_POLY1305_SHA256      				0xCCad

/* chacha20-poly1305 earlier version of nonce and padding (CHACHA_BYTE) */
#define TLS_ECDHE_RSA_WITH_CHACHA20_OLD_POLY1305_SHA256    				0xCC13
#define TLS_ECDHE_ECDSA_WITH_CHACHA20_OLD_POLY1305_SHA256  				0xCC14
#define TLS_DHE_RSA_WITH_CHACHA20_OLD_POLY1305_SHA256      				0xCC15

/* ECDHE_PSK RFC8442, first byte is 0xD0 (ECDHE_PSK_BYTE) */
#define TLS_ECDHE_PSK_WITH_AES_128_GCM_SHA256 						0xD001

/* TLS v1.3 cipher suites */
#define TLS_AES_128_GCM_SHA256       											0x1301
#define TLS_AES_256_GCM_SHA384        										0x1302
#define TLS_CHACHA20_POLY1305_SHA256    									0x1303
#define TLS_AES_128_CCM_SHA256       											0x1304
#define TLS_AES_128_CCM_8_SHA256      										0x1305

/* TLS v1.3 Integrity only cipher suites - 0xC0 (ECC) first byte */
#define TLS_SHA256_SHA256  																0xC0B4
#define TLS_SHA384_SHA384  																0xC0B5


/*
 * SSL version enumeration
*/
typedef enum
{
	SSL_VSN_SSLV30,
	SSL_VSN_TLSV10,
	SSL_VSN_TLSV11,
	SSL_VSN_TLSV12,
	SSL_VSN_TLSV13,
	SSL_VSN_ALL
} SSLVersion;

/*
 * SSL verification enumeration
*/

typedef enum
{
	SSL_VERIFY_MODE_NONE = 0,		// don't verify peer's identification
	SSL_VERIFY_MODE_OPTIONAL = 1,	// verify peer's identification, but continue handshaking when verifies fail
	SSL_VERIFY_MODE_REQUIRED = 2,	// verify peer's identification, but stop handshaking when verifies fail
	SSL_VERIFY_MODE_UNSET = 3 		// Used only for sni_authmode
} SSLPerVerifyMode;

/*
 * SSL certificate structure
*/

typedef char* SSLCertPathPtr;

typedef struct
{
	SSLCertPathPtr rootCA;
	SSLCertPathPtr clientKey;
	SSLCertPathPtr clientCert;
}SSLCertPath;

typedef enum
{
	SSL_CERT_ROOTCA,
	SSL_CERT_CLIENTKEY,
	SSL_CERT_CLIENTCERT
}SSLCertType;

typedef enum
{
	SSL_CERT_FROM_BUF,	// certificates come from buffer
	SSL_CERT_FROM_FS	// certificates come from file system
}SSLCertFrom;

typedef enum
{
	SSL_AUTH_WITH_CERT,	// certificates use cert
	SSL_AUTH_WITH_PSK	// certificates use psk
}SSLPriAuthMode;


typedef struct
{
	unsigned char *data;
	int len;
} clientKeyPassword;

typedef struct
{
	SSLCertFrom from;	// specify where certificates come from
	SSLCertPath path;	// specify certificates path
	clientKeyPassword clientKeyPwd;	// client key password
}SSLCert;

typedef struct
{
	unsigned char *Psk;  		/*Keys are required to be at least 16 bytes long,
													 *this should be binary type*/
	unsigned char Psk_len;	/*The PSK key length*/
	unsigned char *Psk_id; 	/*The PSK identity for PSK negotiation.
													 *this should be string type*/
}SSLPsk;

typedef struct
{
	unsigned int *cipherlist;	/*Ciphersuit list*/
	unsigned int ciphernum;		/*Ciphersuit list number*/
}SSLCipherListPtr;

/*
 * SSL configuration structure
*/

typedef struct
{
	unsigned char* data;
	int len;
} SSLCTRDRBGSeed;


typedef struct
{
	unsigned char protocol;				// 0:SSL/TLS
	unsigned char *serverName;		//server name
	unsigned short serverPort;		//server port
	SSLVersion vsn;								// ssl version
	SSLPerVerifyMode verify;			// verify mode
	SSLPriAuthMode auth;				  // auth mode
	SSLCert cert;									// certificate info
	SSLPsk psk;										// psk info
	SSLCipherListPtr cipherList;	// cipher list pointer
	unsigned char setSNI;					// SNI info
	unsigned char sessionReuseEn;	// whether to reuse previous ssl session on next connection, 0:disable, 1:enable
} SSLConfig;


/*
 * SSL context structure
*/

typedef struct
{
	SSLConfig *config;
	void *SSL;
} SSLCtx;

/*
 * SSL IO optation
*/
#define SSL_OP_BLOCK	"SOC_NBIO"
#define SSL_OP_TIMEOUT	"SOC_TIMEOUT"
/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_set_config
 * DESCRIPTION 
 *          This API is use to ssl set config. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 *        config    [IN]: config
 * RETURN VALUES
 *        NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_ssl_set_config(SSLCtx * sslCtx, SSLConfig* config);


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_ctx_init
 * DESCRIPTION 
 *          This API is use to ssl ctx init. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_ctx_init(SSLCtx * sslCtx);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_ctx_deinit
 * DESCRIPTION 
 *          This API is use to ssl ctx deinit. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 * RETURN VALUES
 *         NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_ssl_ctx_deinit(SSLCtx * sslCtx);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_handshake
 * DESCRIPTION 
 *          This API is use to ssl handshake. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 *        timeout_ms [IN]: timeout_ms
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_handshake(SSLCtx * sslCtx, int timeout_ms);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_write
 * DESCRIPTION 
 *          This API is use to ssl write. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 *        data      [IN]: data
 *        sz        [IN]: data size
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_write(SSLCtx * sslCtx, const void* data, int sz);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_read
 * DESCRIPTION 
 *          This API is use to ssl read. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 *        data      [IN]: data
 *        sz        [IN]: data size
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_read(SSLCtx * sslCtx, void* data, int sz);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_shutdown
 * DESCRIPTION 
 *          This API is use to ssl shutdown. 
 * PARAMETERS 
 *        sslCtx    [IN]: sslCtx
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_shutdown(SSLCtx * sslCtx);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_set_optation
 * DESCRIPTION 
 *          This API is use to set ssl extern optation. 
 * PARAMETERS 
 *        op_name    [IN]: optation name
 *				value			 [IN]: optation value
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_set_optation(char *op_name,void *value);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ssl_get_optation
 * DESCRIPTION 
 *          This API is use to get ssl extern optation. 
 * PARAMETERS 
 *        op_name    [IN]: optation name
 *				value			 [IN]: optation value
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ssl_get_optation(char *op_name,void *value);

#ifdef __cplusplus
}
#endif

#endif

