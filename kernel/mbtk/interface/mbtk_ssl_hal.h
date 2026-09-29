
#ifndef _MBTK_SSL_HAL_H
#define _MBTK_SSL_HAL_H

#ifndef REMOVE_MBEDTLS

#ifdef MBTK_SSL_USE_WOLFSSL
#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/openssl/ssl.h"
#include "wolfssl/internal.h"
#else
#ifndef TLS_3_2_1
#include "mbedtls/config.h"
#endif
#include "mbedtls/debug.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "mbedtls/compat-1.3.h"
#include "mbedtls/net_sockets.h"
#endif
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

typedef struct
{
	unsigned char *data;
	int len;
} clientKeyPassword;

typedef enum
{
	SSL_AUTH_WITH_CERT,	// certificates use cert
	SSL_AUTH_WITH_PSK	// certificates use psk
}SSLPriAuthMode;

typedef struct
{
	SSLCertFrom from;	// specify where certificates come from
	SSLCertPath path;	// specify certificates path
	clientKeyPassword clientKeyPwd;	// client key password
}SSLCert;

typedef struct
{
	unsigned char *Psk;  			/*Keys are required to be at least 16 bytes long,
													 	*this should be binary type*/
	unsigned char Psk_len;		/*The PSK key length*/
	unsigned char *Psk_id; 		/*The PSK identity for PSK negotiation.
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
} SSLConfig,mbtk_ssl_profile;

/*
 * SSL context structure
*/

typedef struct
{
	SSLConfig *config;
	void *SSL;
} SSLCtx;


typedef struct {
	int fd;
#ifdef MBTK_SSL_USE_WOLFSSL
	WOLFSSL_CTX* ctx;
  WOLFSSL* ssl;	
#else
  mbedtls_ssl_context ssl;
	mbedtls_ssl_config config;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_entropy_context entropy; /**< mbed TLS control context. */
	mbedtls_x509_crt *ca_cert;
	mbedtls_x509_crt *client_cert;
	mbedtls_pk_context *client_key;
	char *ca_path;
	char *client_cert_path;
	char *client_key_path;
	mbedtls_ssl_session *saved_session;
#endif
} mbtk_ssl_client_t;


#define MBTK_DEFAULT_CA_PA  "ca.crt"
#define MBTK_DEFAULT_CLI_CERT_PA "client.crt"
#define MBTK_DEFAULT_CLI_KEY_PA "cli_key.crt"

//internal interface start
mbtk_ssl_client_t * mbtk_ssl_client_init(int fd, mbtk_ssl_profile*profile);
void mbtk_ssl_client_shutdown(mbtk_ssl_client_t * client);
mbtk_ssl_profile *mbtk_ssl_profile_new(unsigned char protocol, 
											   const char *host, const unsigned short port,
											   unsigned char verify_type,SSLPriAuthMode auth,
											   SSLVersion version,unsigned char SNI,
											   unsigned char sessionReuseEn);
int mbtk_ssl_profile_set_cert(mbtk_ssl_profile * profile,
	SSLCertFrom cert_type,const char *ca,const char *cli_cert,const char *cli_key);
int mbtk_ssl_profile_set_psk(mbtk_ssl_profile * profile,
	const char* psk,unsigned char psk_len,const char *psk_id);
int mbtk_ssl_profile_set_cipherlist(mbtk_ssl_profile * profile,
	const int *cipherlist,unsigned char list_size);
void mbtk_ssl_profile_free(mbtk_ssl_profile * profile);
int mbtk_ssl_write( void *ssl, char *buf, int len );
int mbtk_ssl_read( void *ssl, char *buf, int len );
//internal interface end

void SSLSetConfig(SSLCtx * sslCtx, SSLConfig* config);

int SSLCtxInit(SSLCtx * sslCtx);

void SSLCtxDeinit(SSLCtx * sslCtx);

int SSLHandshake(SSLCtx * sslCtx, int timeout_ms);

int SSLWrite(SSLCtx * sslCtx, const void* data, int sz);

int SSLRead(SSLCtx * sslCtx, void* data, int sz);

int SSLShutdown(SSLCtx * sslCtx);

int mbtk_ssl_set_optation(char *op_name,void *value);

int mbtk_ssl_get_optation(char *op_name,void *value);


#endif
#endif
