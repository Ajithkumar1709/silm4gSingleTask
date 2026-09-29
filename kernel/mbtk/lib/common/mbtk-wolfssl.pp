//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\async.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\async.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\fips.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\fips.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\fips_test.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\fips_test.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\selftest.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\selftest.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wolfcrypt_first.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wolfcrypt_first.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wolfcrypt_last.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wolfcrypt_last.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\bio.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\bio.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\conf.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\conf.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\crl.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\crl.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dtls.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\dtls.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dtls13.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\dtls13.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\internal.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\internal.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
typedef int ( *AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef char _args_test_ [ ( sizeof ( ( ssl->async->args ) ) ) >= ( sizeof ( ( *args ) ) ) ? 1 : -1 ] ;
typedef char _args_test_ [ ( sizeof ( ( ssl->async->args ) ) ) >= ( sizeof ( ( *args ) ) ) ? 1 : -1 ] ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\keys.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\keys.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ocsp.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ocsp.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pk.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\pk.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\quic.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\quic.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sniffer.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\sniffer.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
typedef WOLFSSL_AES_KEY AES_KEY ;
typedef WOLFSSL_CMAC_CTX CMAC_CTX ;
typedef unsigned char WOLFSSL_DES_cblock [ 8 ] ;
typedef WOLFSSL_DES_cblock WOLFSSL_const_DES_cblock ;
typedef WOLFSSL_DES_cblock WOLFSSL_DES_key_schedule ;
typedef unsigned int WOLFSSL_DES_LONG ;
typedef WOLFSSL_DES_cblock DES_cblock ;
typedef WOLFSSL_const_DES_cblock const_DES_cblock ;
typedef WOLFSSL_DES_key_schedule DES_key_schedule ;
typedef WOLFSSL_DES_LONG DES_LONG ;
typedef WOLFSSL_DRBG_CTX DRBG_CTX ;
typedef void ( *WOLFSSL_CBC128_CB ) ( const unsigned char *in ,
 unsigned char *out , size_t len , const void *key ,
 unsigned char *iv , int enc ) ;
typedef WOLFSSL_RC4_KEY RC4_KEY ;
typedef void * ( *X509V3_EXT_D2I ) ( void * , const unsigned char ** , long ) ;
typedef int ( *X509V3_EXT_I2D ) ( void * , unsigned char ** ) ;
typedef WOLFSSL_STACK WOLFSSL_AUTHORITY_INFO_ACCESS ;
typedef char ok [ sizeof ( md4->buffer ) >= sizeof ( Md4 ) ? 1 : -1 ] ;
typedef char md5_test [ sizeof ( WOLFSSL_MD5_CTX ) >= sizeof ( wc_Md5 ) ? 1 : -1 ] ;
typedef char sha_test [ sizeof ( WOLFSSL_SHA_CTX ) >= sizeof ( wc_Sha ) ? 1 : -1 ] ;
typedef char sha_test [ sizeof ( SHA256_CTX ) >= sizeof ( wc_Sha256 ) ? 1 : -1 ] ;
typedef char aes_test [ sizeof ( AES_KEY ) >= sizeof ( Aes ) ? 1 : -1 ] ;
typedef unsigned long ( idCb ) ( void ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_asn1.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_asn1.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_bn.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_bn.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_certman.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_certman.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_crypto.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_crypto.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_load.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_load.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_misc.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_misc.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_p7p12.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_p7p12.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ssl_sess.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\ssl_sess.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\tls.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\tls.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\tls13.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\tls13.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wolfio.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\wolfio.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef byte ecc_oid_t ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wc_port.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wc_port.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef byte ecc_oid_t ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wc_encrypt.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wc_encrypt.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\x509.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\x509.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\x509_str.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\src\\x509_str.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\aes.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\aes.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\arc4.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\arc4.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\asn.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\asn.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef int ( *wc_AesAuthEncryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef int ( *wc_AesAuthDecryptFunc ) ( Aes* aes , byte* out ,
 const byte* in , word32 sz ,
 const byte* iv , word32 ivSz ,
 const byte* authTag , word32 authTagSz ,
 const byte* authIn , word32 authInSz ) ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef byte ecc_oid_t ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
typedef char WOLFSSL_EVP_MD ;
typedef char WOLFSSL_EVP_CIPHER ;
typedef int WOLFSSL_ENGINE ;
typedef WOLFSSL_EVP_MD EVP_MD ;
typedef WOLFSSL_EVP_MD_CTX EVP_MD_CTX ;
typedef WOLFSSL_EVP_CIPHER EVP_CIPHER ;
typedef WOLFSSL_EVP_CIPHER_CTX EVP_CIPHER_CTX ;
typedef WOLFSSL_ASN1_PCTX ASN1_PCTX ;
typedef WOLFSSL_EVP_PKEY EVP_PKEY ;
typedef WOLFSSL_EVP_PKEY PKCS8_PRIV_KEY_INFO ;
typedef WOLFSSL_ENGINE ENGINE ;
typedef WOLFSSL_EVP_PKEY_CTX EVP_PKEY_CTX ;
typedef unsigned long ( *wolf_sk_hash_cb ) ( const void *v ) ;
typedef WOLFSSL_BIGNUM BIGNUM ;
typedef WOLFSSL_BN_CTX BN_CTX ;
typedef WOLFSSL_BN_GENCB BN_GENCB ;
typedef WOLFSSL_RSA RSA ;
typedef WOLFSSL_RSA_METHOD RSA_METHOD ;
typedef int ( *CallbackIORecv ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *CallbackIOSend ) ( WOLFSSL *ssl , char *buf , int sz , void *ctx ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_verify_cb ) ( int , WOLFSSL_X509_STORE_CTX * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_get_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL ** , WOLFSSL_X509 * ) ;
typedef int ( *WOLFSSL_X509_STORE_CTX_check_crl_cb ) ( WOLFSSL_X509_STORE_CTX * ,
 WOLFSSL_X509_CRL * ) ;
typedef int ( *wolfSSL_BIO_meth_write_cb ) ( WOLFSSL_BIO* , const char* , int ) ;
typedef int ( *wolfSSL_BIO_meth_read_cb ) ( WOLFSSL_BIO * , char * , int ) ;
typedef int ( *wolfSSL_BIO_meth_puts_cb ) ( WOLFSSL_BIO* , const char* ) ;
typedef int ( *wolfSSL_BIO_meth_gets_cb ) ( WOLFSSL_BIO* , char* , int ) ;
typedef long ( *wolfSSL_BIO_meth_ctrl_get_cb ) ( WOLFSSL_BIO* , int , long , void* ) ;
typedef int ( *wolfSSL_BIO_meth_create_cb ) ( WOLFSSL_BIO* ) ;
typedef int ( *wolfSSL_BIO_meth_destroy_cb ) ( WOLFSSL_BIO* ) ;
typedef int wolfSSL_BIO_info_cb ( WOLFSSL_BIO * , int , int ) ;
typedef long ( *wolfssl_BIO_meth_ctrl_info_cb ) ( WOLFSSL_BIO* , int , wolfSSL_BIO_info_cb* ) ;
typedef long ( *wolf_bio_info_cb ) ( WOLFSSL_BIO *bio , int event , const char *parg ,
 int iarg , long larg , long return_value ) ;
typedef char* WOLFSSL_STRING ;
typedef WOLFSSL_METHOD* ( *wolfSSL_method_func ) ( void* heap ) ;
typedef int ( *VerifyCallback ) ( int , WOLFSSL_X509_STORE_CTX* ) ;
typedef void ( CallbackInfoState ) ( const WOLFSSL* ssl , int , int ) ;
typedef int ( *CallbackMcastHighwater ) ( unsigned short peerId ,
 unsigned int maxSeq ,
 unsigned int curSeq , void* ctx ) ;
typedef WOLFSSL_STACK WOLFSSL_GENERAL_NAMES ;
typedef WOLFSSL_STACK WOLFSSL_DIST_POINTS ;
typedef int ( *client_cert_cb ) ( WOLFSSL *ssl , WOLFSSL_X509 **x509 ,
 WOLFSSL_EVP_PKEY **pkey ) ;
typedef int ( *CertSetupCallback ) ( WOLFSSL* ssl , void* ) ;
typedef unsigned int ( *wc_psk_client_callback ) ( WOLFSSL* ssl , const char* , char* ,
 unsigned int , unsigned char* , unsigned int ) ;
typedef int ( *wc_psk_use_session_cb_func ) ( WOLFSSL* ssl ,
 const WOLFSSL_EVP_MD* md , const unsigned char **id ,
 size_t* idlen , WOLFSSL_SESSION **sess ) ;
typedef unsigned int ( *wc_psk_client_cs_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char* ) ;
typedef unsigned int ( *wc_psk_client_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 char* , unsigned int , unsigned char* , unsigned int , const char** ) ;
typedef unsigned int ( *wc_psk_server_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int ) ;
typedef unsigned int ( *wc_psk_server_tls13_callback ) ( WOLFSSL* ssl , const char* ,
 unsigned char* , unsigned int , const char** ) ;
typedef va_list __gnuc_va_list ;
typedef void ( *CallbackCACache ) ( unsigned char* der , int sz , int type ) ;
typedef void ( *CbMissingCRL ) ( const char* url ) ;
typedef int ( *CbOCSPIO ) ( void* , const char* , int ,
 unsigned char* , int , unsigned char** ) ;
typedef void ( *CbOCSPRespFree ) ( void* , unsigned char* ) ;
typedef int ( *CallbackMacEncrypt ) ( WOLFSSL* ssl , unsigned char* macOut ,
 const unsigned char* macIn , unsigned int macInSz , int macContent ,
 int macVerify , unsigned char* encOut , const unsigned char* encIn ,
 unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackDecryptVerify ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackEncryptMac ) ( WOLFSSL* ssl , unsigned char* macOut ,
 int content , int macVerify , unsigned char* encOut ,
 const unsigned char* encIn , unsigned int encSz , void* ctx ) ;
typedef int ( *CallbackVerifyDecrypt ) ( WOLFSSL* ssl ,
 unsigned char* decOut , const unsigned char* decIn ,
 unsigned int decSz , int content , int verify , unsigned int* padSz ,
 void* ctx ) ;
typedef int ( *CallbackSessionTicket ) ( WOLFSSL* ssl , const unsigned char* , int , void* ) ;
typedef int ( *HandShakeDoneCb ) ( WOLFSSL* ssl , void* ) ;
typedef WOLFSSL_MD4_CTX MD4_CTX ;
typedef WOLFSSL_MD5_CTX MD5_CTX ;
typedef WOLFSSL_SHA_CTX SHA_CTX ;
typedef WOLFSSL_SHA256_CTX SHA256_CTX ;
typedef WOLFSSL_SHA3_224_CTX SHA3_224_CTX ;
typedef WOLFSSL_SHA3_256_CTX SHA3_256_CTX ;
typedef WOLFSSL_SHA3_384_CTX SHA3_384_CTX ;
typedef WOLFSSL_SHA3_512_CTX SHA3_512_CTX ;
typedef WOLFSSL_RIPEMD_CTX RIPEMD_CTX ;
typedef void ( *WOLFSSL_BN_CB ) ( int i , int j , void* exArg ) ;
typedef WOLFSSL_DSA DSA ;
typedef int point_conversion_form_t ;
typedef WOLFSSL_EC_KEY EC_KEY ;
typedef WOLFSSL_EC_GROUP EC_GROUP ;
typedef WOLFSSL_EC_GROUP EC_METHOD ;
typedef WOLFSSL_EC_POINT EC_POINT ;
typedef WOLFSSL_EC_BUILTIN_CURVE EC_builtin_curve ;
typedef WOLFSSL_EC_KEY_METHOD EC_KEY_METHOD ;
typedef WOLFSSL_DH DH ;
typedef union {

 WOLFSSL_MD4_CTX md4 ;


 WOLFSSL_MD5_CTX md5 ;


 WOLFSSL_SHA_CTX sha ;





 WOLFSSL_SHA256_CTX sha256 ;
 # 212 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 WOLFSSL_SHA3_224_CTX sha3_224 ;


 WOLFSSL_SHA3_256_CTX sha3_256 ;

 WOLFSSL_SHA3_384_CTX sha3_384 ;

 WOLFSSL_SHA3_512_CTX sha3_512 ;




 } WOLFSSL_Hasher ;
typedef union {

 Aes aes ;
 # 253 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 Des des ;
 Des3 des3 ;

 Arc4 arc4 ;
 # 269 " / mbtk / wolfssl / wolfssl / openssl / evp.h "
 } WOLFSSL_Cipher ;
typedef WOLFSSL_INIT_SETTINGS OPENSSL_INIT_SETTINGS ;
typedef WOLFSSL_CONF CONF ;
typedef WOLFSSL_CONF_VALUE CONF_VALUE ;
typedef WOLFSSL_ECDSA_SIG ECDSA_SIG ;
typedef WOLFSSL SSL ;
typedef WOLFSSL_SESSION SSL_SESSION ;
typedef WOLFSSL_METHOD SSL_METHOD ;
typedef WOLFSSL_CTX SSL_CTX ;
typedef WOLFSSL_X509 X509 ;
typedef WOLFSSL_X509 X509_REQ ;
typedef WOLFSSL_X509_NAME X509_NAME ;
typedef WOLFSSL_X509_INFO X509_INFO ;
typedef WOLFSSL_X509_CHAIN X509_CHAIN ;
typedef WOLFSSL_STACK EXTENDED_KEY_USAGE ;
typedef WOLFSSL_BIO BIO ;
typedef WOLFSSL_BIO_METHOD BIO_METHOD ;
typedef WOLFSSL_CIPHER SSL_CIPHER ;
typedef WOLFSSL_X509_LOOKUP X509_LOOKUP ;
typedef WOLFSSL_X509_LOOKUP_METHOD X509_LOOKUP_METHOD ;
typedef WOLFSSL_X509_CRL X509_CRL ;
typedef WOLFSSL_X509_EXTENSION X509_EXTENSION ;
typedef WOLFSSL_X509_PUBKEY X509_PUBKEY ;
typedef WOLFSSL_X509_ALGOR X509_ALGOR ;
typedef WOLFSSL_ASN1_TIME ASN1_TIME ;
typedef WOLFSSL_ASN1_INTEGER ASN1_INTEGER ;
typedef WOLFSSL_ASN1_OBJECT ASN1_OBJECT ;
typedef WOLFSSL_ASN1_STRING ASN1_STRING ;
typedef WOLFSSL_ASN1_TYPE ASN1_TYPE ;
typedef WOLFSSL_X509_ATTRIBUTE X509_ATTRIBUTE ;
typedef WOLFSSL_ASN1_BIT_STRING ASN1_BIT_STRING ;
typedef WOLFSSL_dynlock_value CRYPTO_dynlock_value ;
typedef WOLFSSL_BUF_MEM BUF_MEM ;
typedef WOLFSSL_GENERAL_NAMES GENERAL_NAMES ;
typedef WOLFSSL_GENERAL_NAME GENERAL_NAME ;
typedef WOLFSSL_OBJ_NAME OBJ_NAME ;
typedef WOLFSSL_DIST_POINT_NAME DIST_POINT_NAME ;
typedef WOLFSSL_DIST_POINT DIST_POINT ;
typedef WOLFSSL_COMP_METHOD COMP_METHOD ;
typedef WOLFSSL_COMP SSL_COMP ;
typedef WOLFSSL_X509_REVOKED X509_REVOKED ;
typedef WOLFSSL_X509_LOOKUP_TYPE X509_LOOKUP_TYPE ;
typedef WOLFSSL_X509_OBJECT X509_OBJECT ;
typedef WOLFSSL_X509_STORE X509_STORE ;
typedef WOLFSSL_X509_STORE_CTX X509_STORE_CTX ;
typedef WOLFSSL_X509_VERIFY_PARAM X509_VERIFY_PARAM ;
typedef int OSSL_HANDSHAKE_STATE ;
typedef WOLFSSL_STACK AUTHORITY_INFO_ACCESS ;
typedef WOLFSSL_X509_NAME_ENTRY X509_NAME_ENTRY ;
typedef WOLFSSL_CONF_CTX SSL_CONF_CTX ;
typedef void ( *wolfSSL_sk_freefunc ) ( void * ) ;
typedef void ( *Rem_Sess_Cb ) ( WOLFSSL_CTX* , WOLFSSL_SESSION* ) ;
typedef void ( *SSL_Msg_Cb ) ( int write_p , int version , int content_type ,
 const void *buf , size_t len , WOLFSSL *ssl , void *arg ) ;
typedef int ( *ticketCompatCb ) ( WOLFSSL *ssl , unsigned char *name , unsigned char *iv ,
 WOLFSSL_EVP_CIPHER_CTX *ectx , WOLFSSL_HMAC_CTX *hctx , int enc ) ;
typedef int ( *tlsextStatusCb ) ( WOLFSSL* ssl , void* ) ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef WOLFSSL_BUFFER_INFO buffer ;
typedef void ( psk_sess_free_cb ) ( const WOLFSSL* ssl , const WOLFSSL_SESSION* sess ,
 psk_sess_free_cb_ctx* freeCtx ) ;
typedef union Digest {

 wc_Sha256 sha256 ;
 # 4324 " / mbtk / wolfssl / wolfssl / internal.h "
 } Digest ;
typedef int ( *hmacfp ) ( WOLFSSL* , byte* , const byte* , word32 , int , int , int , int ) ;
typedef const char* cipher_name ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\coding.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\coding.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cryptocb.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\cryptocb.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\des3.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\des3.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dh.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\dh.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef float float_t ;
typedef double double_t ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\dsa.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\dsa.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\ecc.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\ecc.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef byte ecc_oid_t ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\error.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\error.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\hash.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\hash.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\hmac.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\hmac.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\hpke.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\hpke.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\integer.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\integer.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\kdf.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\kdf.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\logging.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\logging.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef va_list __gnuc_va_list ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\md2.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\md2.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\md4.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\md4.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\md5.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\md5.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\memory.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\memory.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\misc.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\misc.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pkcs12.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\pkcs12.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pkcs7.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\pkcs7.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pwdbased.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\pwdbased.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 149 " / mbtk / wolfssl / wolfssl / wolfcrypt / hmac.h "
 } wc_HmacHash ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\random.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\random.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\rc2.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\rc2.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\rsa.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\rsa.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sha.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sha.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sha256.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sha256.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sha3.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sha3.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sha512.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sha512.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\signature.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\signature.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef int ( wc_pem_password_cb ) ( char* passwd , int sz , int rw , void* userdata ) ;
typedef time_t ( *wc_time_cb ) ( time_t* t ) ;
typedef byte ecc_oid_t ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\siphash.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\siphash.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sm2.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sm2.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sm3.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sm3.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sm4.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sm4.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\srp.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\srp.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\sp_int.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\sp_int.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\tfm.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\tfm.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\curve25519.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\curve25519.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef sword32 fe [ 10 ] ;
typedef const char* curve25519_str ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\fe_operations.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\fe_operations.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef sword32 fe [ 10 ] ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\camellia.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\camellia.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef word32 KEY_TABLE_TYPE [ ( 272 / sizeof ( word32 ) ) ] ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
typedef unsigned int u32 ;
typedef unsigned char u8 ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wolfevent.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wolfevent.c
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\wolfmath.ppp
//PPL Source File Name : \\mbtk\\wolfssl\\wolfcrypt\\src\\wolfmath.c
typedef int wolfSSL_Mutex ;
typedef wolfSSL_Mutex wolfSSL_RwLock ;
typedef void ( mutex_cb ) ( int flag , int type , const char* file , int line ) ;
typedef signed char int8_t ;
typedef signed short int int16_t ;
typedef signed int int32_t ;
typedef signed __int64 int64_t ;
typedef unsigned char uint8_t ;
typedef unsigned short int uint16_t ;
typedef unsigned int uint32_t ;
typedef unsigned __int64 uint64_t ;
typedef signed char int_least8_t ;
typedef signed short int int_least16_t ;
typedef signed int int_least32_t ;
typedef signed __int64 int_least64_t ;
typedef unsigned char uint_least8_t ;
typedef unsigned short int uint_least16_t ;
typedef unsigned int uint_least32_t ;
typedef unsigned __int64 uint_least64_t ;
typedef signed int int_fast8_t ;
typedef signed int int_fast16_t ;
typedef signed int int_fast32_t ;
typedef signed __int64 int_fast64_t ;
typedef unsigned int uint_fast8_t ;
typedef unsigned int uint_fast16_t ;
typedef unsigned int uint_fast32_t ;
typedef unsigned __int64 uint_fast64_t ;
typedef signed int intptr_t ;
typedef unsigned int uintptr_t ;
typedef signed long long intmax_t ;
typedef unsigned long long uintmax_t ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef unsigned char byte ;
typedef signed char sword8 ;
typedef unsigned char word8 ;
typedef short sword16 ;
typedef unsigned short word16 ;
typedef int sword32 ;
typedef unsigned int word32 ;
typedef byte word24 [ 3 ] ;
typedef const char* const wcchar ;
typedef long long sword64 ;
typedef unsigned long long word64 ;
typedef word32 wolfssl_word ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef size_t wc_ptr_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef void * ( *wolfSSL_OSSL_Malloc_cb ) ( size_t , const char * , int ) ;
typedef void ( *wolfSSL_OSSL_Free_cb ) ( void * , const char * , int ) ;
typedef void * ( *wolfSSL_OSSL_Realloc_cb ) ( void * , size_t , const char * , int ) ;
typedef void * ( *wolfSSL_Malloc_cb ) ( size_t size ) ;
typedef void ( *wolfSSL_Free_cb ) ( void *ptr ) ;
typedef void * ( *wolfSSL_Realloc_cb ) ( void *ptr , size_t size ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef void* THREAD_RETURN ;
typedef void* THREAD_TYPE ;
typedef union {

 wc_Md5 md5 ;


 wc_Sha sha ;





 wc_Sha256 sha256 ;
 # 122 " / mbtk / wolfssl / wolfssl / wolfcrypt / hash.h "
 } wc_HashAlg ;
typedef unsigned char sp_uint8 ;
typedef char sp_int8 ;
typedef unsigned short sp_uint16 ;
typedef short sp_int16 ;
typedef unsigned int sp_uint32 ;
typedef int sp_int32 ;
typedef unsigned long long sp_uint64 ;
typedef long long sp_int64 ;
typedef sp_uint32 sp_int_digit ;
typedef sp_int32 sp_int_sdigit ;
typedef sp_uint64 sp_int_word ;
typedef sp_int64 sp_int_sword ;
typedef sp_int32 sp_digit ;
typedef sp_int mp_int ;
typedef sp_int_digit mp_digit ;
typedef void ( *wolfSSL_Logging_cb ) ( const int logLevel ,
 const char *const logMessage ) ;
