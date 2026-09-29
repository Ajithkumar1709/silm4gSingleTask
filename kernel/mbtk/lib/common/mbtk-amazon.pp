//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbtk_aws_iot_fp_api.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-api\\mbtk_aws_iot_fp_api.c
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
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PMU_POR = 1 ,	 
 PMU_EMR ,	 
 PMU_WDTR = ( PMU_EMR+2 )	 
 } PMU_LastResetStatus;

typedef UINT8 UART_Activity ;
//ICAT EXPORTED STRUCT 
 typedef struct /* This is structure of the UART Configuration */ 
 {	 
 UART_OpMode opMode ; /* fifo mode , non fifo mode or DMA for basic interface*/	 
 UART_TriggerLevel triggerLevel ; /* the trigger level interrupt on 1 , 8 , 16 , 32 */	 
 UART_BaudRates baudRate ; /* the rate of the transmit and the receive up to 111520 ( default - 9600 ) .*/	 
 UART_WordLen numDataBits ; /* 5 , 6 , 7 , or 8 number of data bits in the UART data frame ( default - 8 ) . */	 
 UART_StopBits stopBits ; /* 1 , 1.500000 or 2 stop bits in the UART data frame ( default - 1 ) . */	 
 UART_ParityTBits parityBitType ; /* Even , Odd or no-parity bit type in the UART data frame ( default - Non ) . */	 
 UART_InterfaceType interfaceType ; /* number of interface that the UART driver supplies ( default - UART_IF_TYPE_L2 ) */	 
 BOOL modemSignal ; /* enable operate modem - TRUE , disable modem - FALSE */	 
 BOOL flowControl ; /* enable Auto flow Control - TRUE , disable Auto flow Control - FALSE */	 
 UINT8 sleepMode ; /* enable sleep mode - TRUE , more fine control - see UARTSleepMode enum */	 
 BOOL auto_baud ; /* enable auto_baud , auto-baud-rate detection within the UART ( default - FALSE ) */	 
 UART_SIRConfigure sirIrDA ;	 
 } UARTConfiguration;

//ICAT EXPORTED ENUM 
 typedef enum // change the order -1 to + 
 {	 
 UART_RC_OK = 1 , /* 1 - no errors */	 
	 
 UART_RC_PORT_NUM_ERROR = -100 , /* -100 - Error in the UART port number */	 
 UART_RC_NO_DATA_TO_READ , /* -99 - Eror no data to read from the FIFO UART */	 
 UART_RC_ILLEGAL_BAUD_RATE , /* -98 - Error in the UART Bayd Rate */	 
 UART_RC_UART_PARITY_BITS_ERROR , /* -97 - Error in parity bit */	 
 UART_RC_UART_ONE_STOP_BIT_ERROR , /* -96 - Error in one stop bit */	 
 UART_RC_ONE_HALF_OR_TWO_STOP_BIT_ERROR , /* -95 - Error in two stop bit */	 
 UART_RC_BAD_INTERFACE_TYPE , /* -94 - Error in the Interface Type */	 
 UART_RC_UART_NOT_AVAILABLE , /* -93 - Error in try to open UART that is open */	 
 UART_RC_NO_DATA_TO_WRITE , /* -92 - Error No data to writ the len = 0 */	 
 UART_RC_NOT_ALL_BYTE_WRITTEN , /* -91 - Error Not all the Byte write to the UART FIFO */	 
 UART_RC_ISR_ALREADY_BIND , /* -90 - Error try to bind ISR for Basic Interface */	 
 UART_RC_WRONG_ISR_UNBIND , /* -89 - Error in the UnBind ISR for Basic Interface */	 
 UART_RC_FIFO_NOT_EMPTY , /* -88 - Error , the UART FIFO not empty */	 
 UART_RC_UART_OPEN , /* -87 - Error try chance the configurr when the UART open */	 
 UART_RC_GPIO_ERR , /* -86 - Error in the Configure of the GPIO */	 
 UART_RC_IRDA_CONFIG_ERR , /* -85 - Illegal IrDA configuration */	 
 UART_RC_TX_DMA_ERR /* -84 - DMA TX Error */	 
 } UART_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 LOG_DISABLE = 0x0 ,	 
 UART_LOG_ENABLE = 0x1 ,	 
 ACAT_LOG_ENABLE = 0x2	 
 } Log_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 MSG_DISABLE = 0x0 ,	 
 ACAT_MSG_ENABLE = 0x1	 
 } Msg_ConfigE;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RTI_LOG_DISABLE = 0x0 ,	 
 RTI_DUMP_ENABLE = 0x1 ,	 
 RTI_TASK_ENABLE = 0x2 ,	 
 RTI_MIPS_ENABLE = 0x3	 
 } RTI_ConfigE;

//ICAT EXPORTED STRUCT 
 typedef struct {	 
 Log_ConfigE log_cfg ;	 
 Msg_ConfigE msg_cfg ;	 
 RTI_ConfigE rti_cfg ;	 
 } Log_ConfigS;

typedef void ( *UARTNotifyInterrupt ) ( UART_Port ) ;
typedef void ( *UsbLogPrint_t ) ( const char * , ... ) ;
typedef int mbedtls_iso_c_forbids_empty_translation_units ;
typedef int32_t mbedtls_mpi_sint ;
typedef uint32_t mbedtls_mpi_uint ;
typedef uint64_t mbedtls_t_udbl ;
typedef void mbedtls_ecp_restart_ctx ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef INT ssize_t ;
typedef ULONG pthread_t ;
typedef UINT pthread_key_t ;
typedef void ( *destructor_func_t ) ( void* ) ;
typedef ULONG mode_t ;
typedef sem_t *SEM_ID ;
typedef mbedtls_ecp_keypair mbedtls_ecdsa_context ;
typedef void mbedtls_ecdsa_restart_ctx ;
typedef void mbedtls_pk_restart_ctx ;
typedef int ( *mbedtls_pk_rsa_alt_decrypt_func ) ( void *ctx , int mode , size_t *olen ,
 const unsigned char *input , unsigned char *output ,
 size_t output_max_len ) ;
typedef int ( *mbedtls_pk_rsa_alt_sign_func ) ( void *ctx ,
 int ( *f_rng ) ( void * , unsigned char * , size_t ) , void *p_rng ,
 int mode , mbedtls_md_type_t md_alg , unsigned int hashlen ,
 const unsigned char *hash , unsigned char *sig ) ;
typedef size_t ( *mbedtls_pk_rsa_alt_key_len_func ) ( void *ctx ) ;
typedef mbedtls_asn1_buf mbedtls_x509_buf ;
typedef mbedtls_asn1_bitstring mbedtls_x509_bitstring ;
typedef mbedtls_asn1_named_data mbedtls_x509_name ;
typedef mbedtls_asn1_sequence mbedtls_x509_sequence ;
typedef void mbedtls_x509_crt_restart_ctx ;
typedef int ( *mbedtls_x509_crt_ca_cb_t ) ( void *p_ctx ,
 mbedtls_x509_crt const *child ,
 mbedtls_x509_crt **candidate_cas ) ;
typedef time_t mbedtls_time_t ;
typedef int mbedtls_ssl_send_t ( void *ctx ,
 const unsigned char *buf ,
 size_t len ) ;
typedef int mbedtls_ssl_recv_t ( void *ctx ,
 unsigned char *buf ,
 size_t len ) ;
typedef int mbedtls_ssl_recv_timeout_t ( void *ctx ,
 unsigned char *buf ,
 size_t len ,
 uint32_t timeout ) ;
typedef void mbedtls_ssl_set_timer_t ( void * ctx ,
 uint32_t int_ms ,
 uint32_t fin_ms ) ;
typedef int mbedtls_ssl_get_timer_t ( void * ctx ) ;
typedef int mbedtls_ssl_ticket_write_t ( void *p_ticket ,
 const mbedtls_ssl_session *session ,
 unsigned char *start ,
 const unsigned char *end ,
 size_t *tlen ,
 uint32_t *lifetime ) ;
typedef int mbedtls_ssl_ticket_parse_t ( void *p_ticket ,
 mbedtls_ssl_session *session ,
 unsigned char *buf ,
 size_t len ) ;
typedef int mbedtls_ssl_cookie_write_t ( void *ctx ,
 unsigned char **p , unsigned char *end ,
 const unsigned char *info , size_t ilen ) ;
typedef int mbedtls_ssl_cookie_check_t ( void *ctx ,
 const unsigned char *cookie , size_t clen ,
 const unsigned char *info , size_t ilen ) ;
typedef int ( *mbedtls_entropy_f_source_ptr ) ( void *data , unsigned char *output , size_t len ,
 size_t *olen ) ;
typedef void ( *interceptor_handler_t ) ( void* client , message_data_t* msg ) ;
typedef void ( *message_handler_t ) ( void* client , message_data_t* msg ) ;
typedef void ( *reconnect_handler_t ) ( void* client , void* reconnect_date ) ;
typedef void ( *error_handler_t ) ( void *client , mqtt_error_t error ) ;
typedef void ( *mqtt_callback_handler_t ) ( void* client , mqtt_cmd_id_t cmd_id , mqtt_error_t error ) ;
DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\core_pkcs11.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\core_pkcs11.c
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
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
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\core_pki_utils.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\core_pki_utils.c
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
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef unsigned int size_t ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\core_pkcs11_pal.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\portable\\os\\posix\\core_pkcs11_pal.c
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
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
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\core_pkcs11_mbedtls.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\portable\\mbedtls\\core_pkcs11_mbedtls.c
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
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
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef int mbedtls_iso_c_forbids_empty_translation_units ;
typedef int32_t mbedtls_mpi_sint ;
typedef uint32_t mbedtls_mpi_uint ;
typedef uint64_t mbedtls_t_udbl ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef INT ssize_t ;
typedef ULONG pthread_t ;
typedef UINT pthread_key_t ;
typedef void ( *destructor_func_t ) ( void* ) ;
typedef ULONG mode_t ;
typedef sem_t *SEM_ID ;
typedef void mbedtls_ecp_restart_ctx ;
typedef mbedtls_ecp_keypair mbedtls_ecdsa_context ;
typedef void mbedtls_ecdsa_restart_ctx ;
typedef void mbedtls_pk_restart_ctx ;
typedef int ( *mbedtls_pk_rsa_alt_decrypt_func ) ( void *ctx , int mode , size_t *olen ,
 const unsigned char *input , unsigned char *output ,
 size_t output_max_len ) ;
typedef int ( *mbedtls_pk_rsa_alt_sign_func ) ( void *ctx ,
 int ( *f_rng ) ( void * , unsigned char * , size_t ) , void *p_rng ,
 int mode , mbedtls_md_type_t md_alg , unsigned int hashlen ,
 const unsigned char *hash , unsigned char *sig ) ;
typedef size_t ( *mbedtls_pk_rsa_alt_key_len_func ) ( void *ctx ) ;
typedef mbedtls_asn1_buf mbedtls_x509_buf ;
typedef mbedtls_asn1_bitstring mbedtls_x509_bitstring ;
typedef mbedtls_asn1_named_data mbedtls_x509_name ;
typedef mbedtls_asn1_sequence mbedtls_x509_sequence ;
typedef void mbedtls_x509_crt_restart_ctx ;
typedef int ( *mbedtls_x509_crt_ca_cb_t ) ( void *p_ctx ,
 mbedtls_x509_crt const *child ,
 mbedtls_x509_crt **candidate_cas ) ;
typedef int ( *mbedtls_entropy_f_source_ptr ) ( void *data , unsigned char *output , size_t len ,
 size_t *olen ) ;
typedef time_t mbedtls_time_t ;
DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Warn , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\core_pkcs11_pal_utils.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\portable\\os\\core_pkcs11_pal_utils.c
typedef unsigned int size_t ;
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
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
DIAG_FILTER ( MIFI , AWS , Debug , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\pkcs11_operations.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-api\\pkcs11_operations.c
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
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
typedef unsigned char CK_BYTE ;
typedef CK_BYTE CK_CHAR ;
typedef CK_BYTE CK_UTF8CHAR ;
typedef CK_BYTE CK_BBOOL ;
typedef unsigned long int CK_ULONG ;
typedef long int CK_LONG ;
typedef CK_ULONG CK_FLAGS ;
typedef CK_BYTE * CK_BYTE_PTR ;
typedef CK_CHAR * CK_CHAR_PTR ;
typedef CK_UTF8CHAR * CK_UTF8CHAR_PTR ;
typedef CK_ULONG * CK_ULONG_PTR ;
typedef void * CK_VOID_PTR ;
typedef CK_VOID_PTR * CK_VOID_PTR_PTR ;
typedef CK_VERSION * CK_VERSION_PTR ;
typedef CK_INFO * CK_INFO_PTR ;
typedef CK_ULONG CK_NOTIFICATION ;
typedef CK_ULONG CK_SLOT_ID ;
typedef CK_SLOT_ID * CK_SLOT_ID_PTR ;
typedef CK_SLOT_INFO * CK_SLOT_INFO_PTR ;
typedef CK_TOKEN_INFO * CK_TOKEN_INFO_PTR ;
typedef CK_ULONG CK_SESSION_HANDLE ;
typedef CK_SESSION_HANDLE * CK_SESSION_HANDLE_PTR ;
typedef CK_ULONG CK_USER_TYPE ;
typedef CK_ULONG CK_STATE ;
typedef CK_SESSION_INFO * CK_SESSION_INFO_PTR ;
typedef CK_ULONG CK_OBJECT_HANDLE ;
typedef CK_OBJECT_HANDLE * CK_OBJECT_HANDLE_PTR ;
typedef CK_ULONG CK_OBJECT_CLASS ;
typedef CK_OBJECT_CLASS * CK_OBJECT_CLASS_PTR ;
typedef CK_ULONG CK_HW_FEATURE_TYPE ;
typedef CK_ULONG CK_KEY_TYPE ;
typedef CK_ULONG CK_CERTIFICATE_TYPE ;
typedef CK_ULONG CK_ATTRIBUTE_TYPE ;
typedef CK_ATTRIBUTE * CK_ATTRIBUTE_PTR ;
typedef CK_ULONG CK_MECHANISM_TYPE ;
typedef CK_MECHANISM_TYPE * CK_MECHANISM_TYPE_PTR ;
typedef CK_MECHANISM * CK_MECHANISM_PTR ;
typedef CK_MECHANISM_INFO * CK_MECHANISM_INFO_PTR ;
typedef CK_ULONG CK_RV ;
typedef CK_RV ( * CK_NOTIFY ) (
 CK_SESSION_HANDLE hSession ,
 CK_NOTIFICATION event ,
 CK_VOID_PTR pApplication
 ) ;
typedef CK_FUNCTION_LIST * CK_FUNCTION_LIST_PTR ;
typedef CK_FUNCTION_LIST_PTR * CK_FUNCTION_LIST_PTR_PTR ;
typedef CK_RV ( * CK_CREATEMUTEX ) (
 CK_VOID_PTR_PTR ppMutex
 ) ;
typedef CK_RV ( * CK_DESTROYMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_LOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_RV ( * CK_UNLOCKMUTEX ) (
 CK_VOID_PTR pMutex
 ) ;
typedef CK_C_INITIALIZE_ARGS * CK_C_INITIALIZE_ARGS_PTR ;
typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE ;
typedef CK_RSA_PKCS_MGF_TYPE * CK_RSA_PKCS_MGF_TYPE_PTR ;
typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE ;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE * CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR ;
typedef CK_RSA_PKCS_OAEP_PARAMS * CK_RSA_PKCS_OAEP_PARAMS_PTR ;
typedef CK_RSA_PKCS_PSS_PARAMS * CK_RSA_PKCS_PSS_PARAMS_PTR ;
typedef CK_ULONG CK_EC_KDF_TYPE ;
typedef CK_ECDH1_DERIVE_PARAMS * CK_ECDH1_DERIVE_PARAMS_PTR ;
typedef CK_ECDH2_DERIVE_PARAMS * CK_ECDH2_DERIVE_PARAMS_PTR ;
typedef CK_ECMQV_DERIVE_PARAMS * CK_ECMQV_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_X9_42_DH_KDF_TYPE ;
typedef CK_X9_42_DH_KDF_TYPE * CK_X9_42_DH_KDF_TYPE_PTR ;
typedef CK_X9_42_DH2_DERIVE_PARAMS * CK_X9_42_DH2_DERIVE_PARAMS_PTR ;
typedef CK_X9_42_MQV_DERIVE_PARAMS * CK_X9_42_MQV_DERIVE_PARAMS_PTR ;
typedef CK_KEA_DERIVE_PARAMS * CK_KEA_DERIVE_PARAMS_PTR ;
typedef CK_ULONG CK_RC2_PARAMS ;
typedef CK_RC2_PARAMS * CK_RC2_PARAMS_PTR ;
typedef CK_RC2_CBC_PARAMS * CK_RC2_CBC_PARAMS_PTR ;
typedef CK_RC2_MAC_GENERAL_PARAMS * CK_RC2_MAC_GENERAL_PARAMS_PTR ;
typedef CK_RC5_PARAMS * CK_RC5_PARAMS_PTR ;
typedef CK_RC5_CBC_PARAMS * CK_RC5_CBC_PARAMS_PTR ;
typedef CK_RC5_MAC_GENERAL_PARAMS * CK_RC5_MAC_GENERAL_PARAMS_PTR ;
typedef CK_ULONG CK_MAC_GENERAL_PARAMS ;
typedef CK_MAC_GENERAL_PARAMS * CK_MAC_GENERAL_PARAMS_PTR ;
typedef CK_DES_CBC_ENCRYPT_DATA_PARAMS * CK_DES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS * CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_SKIPJACK_PRIVATE_WRAP_PARAMS * CK_SKIPJACK_PRIVATE_WRAP_PARAMS_PTR ;
typedef CK_SKIPJACK_RELAYX_PARAMS * CK_SKIPJACK_RELAYX_PARAMS_PTR ;
typedef CK_PBE_PARAMS * CK_PBE_PARAMS_PTR ;
typedef CK_KEY_WRAP_SET_OAEP_PARAMS * CK_KEY_WRAP_SET_OAEP_PARAMS_PTR ;
typedef CK_SSL3_KEY_MAT_OUT * CK_SSL3_KEY_MAT_OUT_PTR ;
typedef CK_SSL3_KEY_MAT_PARAMS * CK_SSL3_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_PRF_PARAMS * CK_TLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_RANDOM_DATA * CK_WTLS_RANDOM_DATA_PTR ;
typedef CK_WTLS_MASTER_KEY_DERIVE_PARAMS * CK_WTLS_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_WTLS_PRF_PARAMS * CK_WTLS_PRF_PARAMS_PTR ;
typedef CK_WTLS_KEY_MAT_OUT * CK_WTLS_KEY_MAT_OUT_PTR ;
typedef CK_WTLS_KEY_MAT_PARAMS * CK_WTLS_KEY_MAT_PARAMS_PTR ;
typedef CK_CMS_SIG_PARAMS * CK_CMS_SIG_PARAMS_PTR ;
typedef CK_KEY_DERIVATION_STRING_DATA * CK_KEY_DERIVATION_STRING_DATA_PTR ;
typedef CK_ULONG CK_EXTRACT_PARAMS ;
typedef CK_EXTRACT_PARAMS * CK_EXTRACT_PARAMS_PTR ;
typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE ;
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE * CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR ;
typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE ;
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE * CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS * CK_PKCS5_PBKD2_PARAMS_PTR ;
typedef CK_PKCS5_PBKD2_PARAMS2 * CK_PKCS5_PBKD2_PARAMS2_PTR ;
typedef CK_ULONG CK_OTP_PARAM_TYPE ;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE ;
typedef CK_OTP_PARAM * CK_OTP_PARAM_PTR ;
typedef CK_OTP_PARAMS * CK_OTP_PARAMS_PTR ;
typedef CK_OTP_SIGNATURE_INFO * CK_OTP_SIGNATURE_INFO_PTR ;
typedef CK_KIP_PARAMS * CK_KIP_PARAMS_PTR ;
typedef CK_AES_CTR_PARAMS * CK_AES_CTR_PARAMS_PTR ;
typedef CK_GCM_PARAMS * CK_GCM_PARAMS_PTR ;
typedef CK_CCM_PARAMS * CK_CCM_PARAMS_PTR ;
typedef CK_AES_GCM_PARAMS * CK_AES_GCM_PARAMS_PTR ;
typedef CK_AES_CCM_PARAMS * CK_AES_CCM_PARAMS_PTR ;
typedef CK_CAMELLIA_CTR_PARAMS * CK_CAMELLIA_CTR_PARAMS_PTR ;
typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS * CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS * CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_DSA_PARAMETER_GEN_PARAM * CK_DSA_PARAMETER_GEN_PARAM_PTR ;
typedef CK_ECDH_AES_KEY_WRAP_PARAMS * CK_ECDH_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN ;
typedef CK_ULONG CK_CERTIFICATE_CATEGORY ;
typedef CK_RSA_AES_KEY_WRAP_PARAMS * CK_RSA_AES_KEY_WRAP_PARAMS_PTR ;
typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS * CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR ;
typedef CK_TLS12_KEY_MAT_PARAMS * CK_TLS12_KEY_MAT_PARAMS_PTR ;
typedef CK_TLS_KDF_PARAMS * CK_TLS_KDF_PARAMS_PTR ;
typedef CK_TLS_MAC_PARAMS * CK_TLS_MAC_PARAMS_PTR ;
typedef CK_GOSTR3410_DERIVE_PARAMS * CK_GOSTR3410_DERIVE_PARAMS_PTR ;
typedef CK_GOSTR3410_KEY_WRAP_PARAMS * CK_GOSTR3410_KEY_WRAP_PARAMS_PTR ;
typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS * CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR ;
typedef CK_RV ( * CK_C_Initialize )

 (
 CK_VOID_PTR pInitArgs
 ) ;
typedef CK_RV ( * CK_C_Finalize )

 (
 CK_VOID_PTR pReserved
 ) ;
typedef CK_RV ( * CK_C_GetInfo )

 (
 CK_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetFunctionList )

 (
 CK_FUNCTION_LIST_PTR_PTR ppFunctionList
 ) ;
typedef CK_RV ( * CK_C_GetSlotList )

 (
 CK_BBOOL tokenPresent ,
 CK_SLOT_ID_PTR pSlotList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetSlotInfo )

 (
 CK_SLOT_ID slotID ,
 CK_SLOT_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetTokenInfo )

 (
 CK_SLOT_ID slotID ,
 CK_TOKEN_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetMechanismList )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE_PTR pMechanismList ,
 CK_ULONG_PTR pulCount
 ) ;
typedef CK_RV ( * CK_C_GetMechanismInfo )

 (
 CK_SLOT_ID slotID ,
 CK_MECHANISM_TYPE type ,
 CK_MECHANISM_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_InitToken )

 (
 CK_SLOT_ID slotID ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen ,
 CK_UTF8CHAR_PTR pLabel
 ) ;
typedef CK_RV ( * CK_C_InitPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_SetPIN )

 (
 CK_SESSION_HANDLE hSession ,
 CK_UTF8CHAR_PTR pOldPin ,
 CK_ULONG ulOldLen ,
 CK_UTF8CHAR_PTR pNewPin ,
 CK_ULONG ulNewLen
 ) ;
typedef CK_RV ( * CK_C_OpenSession )

 (
 CK_SLOT_ID slotID ,
 CK_FLAGS flags ,
 CK_VOID_PTR pApplication ,
 CK_NOTIFY Notify ,
 CK_SESSION_HANDLE_PTR phSession
 ) ;
typedef CK_RV ( * CK_C_CloseSession )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CloseAllSessions )

 (
 CK_SLOT_ID slotID
 ) ;
typedef CK_RV ( * CK_C_GetSessionInfo )

 (
 CK_SESSION_HANDLE hSession ,
 CK_SESSION_INFO_PTR pInfo
 ) ;
typedef CK_RV ( * CK_C_GetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG_PTR pulOperationStateLen
 ) ;
typedef CK_RV ( * CK_C_SetOperationState )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pOperationState ,
 CK_ULONG ulOperationStateLen ,
 CK_OBJECT_HANDLE hEncryptionKey ,
 CK_OBJECT_HANDLE hAuthenticationKey
 ) ;
typedef CK_RV ( * CK_C_Login )

 (
 CK_SESSION_HANDLE hSession ,
 CK_USER_TYPE userType ,
 CK_UTF8CHAR_PTR pPin ,
 CK_ULONG ulPinLen
 ) ;
typedef CK_RV ( * CK_C_Logout )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CreateObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phObject
 ) ;
typedef CK_RV ( * CK_C_CopyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phNewObject
 ) ;
typedef CK_RV ( * CK_C_DestroyObject )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject
 ) ;
typedef CK_RV ( * CK_C_GetObjectSize )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ULONG_PTR pulSize
 ) ;
typedef CK_RV ( * CK_C_GetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_SetAttributeValue )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hObject ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount
 ) ;
typedef CK_RV ( * CK_C_FindObjects )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE_PTR phObject ,
 CK_ULONG ulMaxObjectCount ,
 CK_ULONG_PTR pulObjectCount
 ) ;
typedef CK_RV ( * CK_C_FindObjectsFinal )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_EncryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Encrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG_PTR pulEncryptedDataLen
 ) ;
typedef CK_RV ( * CK_C_EncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_EncryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastEncryptedPart ,
 CK_ULONG_PTR pulLastEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Decrypt )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedData ,
 CK_ULONG ulEncryptedDataLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DecryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pLastPart ,
 CK_ULONG_PTR pulLastPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism
 ) ;
typedef CK_RV ( * CK_C_Digest )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_DigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_DigestKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_DigestFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pDigest ,
 CK_ULONG_PTR pulDigestLen
 ) ;
typedef CK_RV ( * CK_C_SignInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Sign )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_SignRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_SignRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG_PTR pulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_Verify )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pData ,
 CK_ULONG ulDataLen ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen
 ) ;
typedef CK_RV ( * CK_C_VerifyFinal )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen
 ) ;
typedef CK_RV ( * CK_C_VerifyRecoverInit )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hKey
 ) ;
typedef CK_RV ( * CK_C_VerifyRecover )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSignature ,
 CK_ULONG ulSignatureLen ,
 CK_BYTE_PTR pData ,
 CK_ULONG_PTR pulDataLen
 ) ;
typedef CK_RV ( * CK_C_DigestEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptDigestUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_SignEncryptUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pPart ,
 CK_ULONG ulPartLen ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG_PTR pulEncryptedPartLen
 ) ;
typedef CK_RV ( * CK_C_DecryptVerifyUpdate )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pEncryptedPart ,
 CK_ULONG ulEncryptedPartLen ,
 CK_BYTE_PTR pPart ,
 CK_ULONG_PTR pulPartLen
 ) ;
typedef CK_RV ( * CK_C_GenerateKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_GenerateKeyPair )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_ATTRIBUTE_PTR pPublicKeyTemplate ,
 CK_ULONG ulPublicKeyAttributeCount ,
 CK_ATTRIBUTE_PTR pPrivateKeyTemplate ,
 CK_ULONG ulPrivateKeyAttributeCount ,
 CK_OBJECT_HANDLE_PTR phPublicKey ,
 CK_OBJECT_HANDLE_PTR phPrivateKey
 ) ;
typedef CK_RV ( * CK_C_WrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hWrappingKey ,
 CK_OBJECT_HANDLE hKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG_PTR pulWrappedKeyLen
 ) ;
typedef CK_RV ( * CK_C_UnwrapKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hUnwrappingKey ,
 CK_BYTE_PTR pWrappedKey ,
 CK_ULONG ulWrappedKeyLen ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_DeriveKey )

 (
 CK_SESSION_HANDLE hSession ,
 CK_MECHANISM_PTR pMechanism ,
 CK_OBJECT_HANDLE hBaseKey ,
 CK_ATTRIBUTE_PTR pTemplate ,
 CK_ULONG ulAttributeCount ,
 CK_OBJECT_HANDLE_PTR phKey
 ) ;
typedef CK_RV ( * CK_C_SeedRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR pSeed ,
 CK_ULONG ulSeedLen
 ) ;
typedef CK_RV ( * CK_C_GenerateRandom )

 (
 CK_SESSION_HANDLE hSession ,
 CK_BYTE_PTR RandomData ,
 CK_ULONG ulRandomLen
 ) ;
typedef CK_RV ( * CK_C_GetFunctionStatus )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_CancelFunction )

 (
 CK_SESSION_HANDLE hSession
 ) ;
typedef CK_RV ( * CK_C_WaitForSlotEvent )

 (
 CK_FLAGS flags ,
 CK_SLOT_ID_PTR pSlot ,
 CK_VOID_PTR pRserved
 ) ;
typedef unsigned int size_t ;
typedef unsigned int size_t ;
typedef va_list __gnuc_va_list ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
typedef int mbedtls_iso_c_forbids_empty_translation_units ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef INT ssize_t ;
typedef ULONG pthread_t ;
typedef UINT pthread_key_t ;
typedef void ( *destructor_func_t ) ( void* ) ;
typedef ULONG mode_t ;
typedef sem_t *SEM_ID ;
typedef int ( *mbedtls_entropy_f_source_ptr ) ( void *data , unsigned char *output , size_t len ,
 size_t *olen ) ;
typedef int32_t mbedtls_mpi_sint ;
typedef uint32_t mbedtls_mpi_uint ;
typedef uint64_t mbedtls_t_udbl ;
typedef void mbedtls_ecp_restart_ctx ;
typedef mbedtls_ecp_keypair mbedtls_ecdsa_context ;
typedef void mbedtls_ecdsa_restart_ctx ;
typedef void mbedtls_pk_restart_ctx ;
typedef int ( *mbedtls_pk_rsa_alt_decrypt_func ) ( void *ctx , int mode , size_t *olen ,
 const unsigned char *input , unsigned char *output ,
 size_t output_max_len ) ;
typedef int ( *mbedtls_pk_rsa_alt_sign_func ) ( void *ctx ,
 int ( *f_rng ) ( void * , unsigned char * , size_t ) , void *p_rng ,
 int mode , mbedtls_md_type_t md_alg , unsigned int hashlen ,
 const unsigned char *hash , unsigned char *sig ) ;
typedef size_t ( *mbedtls_pk_rsa_alt_key_len_func ) ( void *ctx ) ;
typedef mbedtls_asn1_buf mbedtls_x509_buf ;
typedef mbedtls_asn1_bitstring mbedtls_x509_bitstring ;
typedef mbedtls_asn1_named_data mbedtls_x509_name ;
typedef mbedtls_asn1_sequence mbedtls_x509_sequence ;
typedef void mbedtls_x509_crt_restart_ctx ;
typedef int ( *mbedtls_x509_crt_ca_cb_t ) ( void *p_ctx ,
 mbedtls_x509_crt const *child ,
 mbedtls_x509_crt **candidate_cas ) ;
DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Info , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\fleet_provisioning_serializer.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-api\\fleet_provisioning_serializer.c
typedef va_list __gnuc_va_list ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef unsigned int size_t ;
typedef uint64_t CborTag ;
typedef CborError ( *CborStreamFunction ) ( void *token , const char *fmt , ... )

 __attribute__ ( ( __format__ ( printf , 2 , 3 ) ) )

 ;
typedef unsigned int size_t ;
typedef unsigned char BOOL ;
typedef unsigned char UINT8 ;
typedef unsigned short UINT16 ;
typedef unsigned long UINT32 ;
typedef char CHAR ;
typedef signed char INT8 ;
typedef signed short INT16 ;
typedef signed long INT32 ;
typedef unsigned char Bool ;
typedef UINT8 BYTE ;
typedef UINT8 UBYTE ;
typedef UINT16 UWORD ;
typedef UINT16 WORD ;
typedef INT16 SWORD ;
typedef UINT32 DWORD ;
typedef unsigned long long UINT64 ;
typedef void* VOID_PTR ;
typedef volatile UINT8 *V_UINT8_PTR ;
typedef volatile UINT16 *V_UINT16_PTR ;
typedef volatile UINT32 *V_UINT32_PTR ;
typedef unsigned int U32Bits ;
typedef BOOL BOOLEAN ;
typedef const char * SwVersion ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 OSA_TASK_READY ,	 
 OSA_TASK_COMPLETED ,	 
 OSA_TASK_TERMINATED ,	 
 OSA_TASK_SUSPENDED ,	 
 OSA_TASK_SLEEP ,	 
 OSA_TASK_QUEUE_SUSP ,	 
 OSA_TASK_SEMAPHORE_SUSP ,	 
 OSA_TASK_EVENT_FLAG ,	 
 OSA_TASK_BLOCK_MEMORY ,	 
 OSA_TASK_MUTEX_SUSP ,	 
 OSA_TASK_STATE_UNKNOWN ,	 
 } OSA_TASK_STATE;

//ICAT EXPORTED STRUCT 
 typedef struct OSA_TASK_STRUCT 
 {	 
 char *task_name ; /* Pointer to thread ' s name */	 
 unsigned int task_priority ; /* Priority of thread ( 0 -255 ) */	 
 unsigned long task_stack_def_val ; /* default vaule of thread */	 
 OSA_TASK_STATE task_state ; /* Thread ' s execution state */	 
 unsigned long task_stack_ptr ; /* Thread ' s stack pointer */	 
 unsigned long task_stack_start ; /* Stack starting address */	 
 unsigned long task_stack_end ; /* Stack ending address */	 
 unsigned long task_stack_size ; /* Stack size */	 
 unsigned long task_run_count ; /* Thread ' s run counter */	 
	 
 } OSA_TASK;

typedef void *OsaRefT ;
typedef UINT8 OSA_STATUS ;
typedef UINT8 OS_STATUS ;
typedef void* OS_HISR ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSASemaRef ;
typedef void* OSAMutexRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPoolRef ;
typedef void* OSATimerRef ;
typedef void* OSAFlagRef ;
typedef void* OSAPartitionPoolRef ;
typedef void* OSTaskRef ;
typedef void* OSSemaRef ;
typedef void* OSMutexRef ;
typedef void* OSMsgQRef ;
typedef void* OSMailboxQRef ;
typedef void* OSPoolRef ;
typedef void* OSTimerRef ;
typedef void* OSFlagRef ;
typedef UINT8 OS_STATUS ;
typedef OsaTimerStatusParamsT OSATimerStatus ;
typedef void* OSATaskRef ;
typedef void* OSAHISRRef ;
typedef void* OSAMsgQRef ;
typedef void* OSAMailboxQRef ;
typedef void* OSAPartitionPoolRef ;
typedef UINT8 OS_STATUS ;
typedef unsigned long UNSIGNED ;
typedef long SIGNED ;
typedef unsigned char DATA_ELEMENT ;
typedef DATA_ELEMENT OPTION ;
typedef DATA_ELEMENT BOOLEAN ;
typedef int STATUS ;
typedef unsigned char UNSIGNED_CHAR ;
typedef unsigned int UNSIGNED_INT ;
typedef int INT ;
typedef unsigned long * UNSIGNED_PTR ;
typedef unsigned char * BYTE_PTR ;
typedef void ( *CommandAddress ) ( void ) ;
typedef char* CommandProto ;
typedef const char * DiagDBVersion ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PROTOCOL_TYPE_0 = 0 ,	 
 MAX_PROTOCOL_TYPES	 
 } ProtocolType;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 BOOL bEnabled ; // enable / disable the trace logging feature	 
 ProtocolType eProtocolType ; // protocol type for communication with ICAT , currently only protocol type 0 is supported	 
 UINT16 nMaxDataPerTrace ; // for each trace , what is the maximum data length to accompany the trace , in protocol type 0 , this is relevant only to DSP messages	 
 } DiagLoggerDefs;

typedef void ( *TIMER_CALLBACK_FUNCTION ) ( UINT8 ) ;
typedef void ( *ACC_TIMER_CALLBACK ) ( UINT32 ) ;
typedef int TIMER_STATUS ;
typedef int TIMER_ID ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 PM_RC_OK = 0 ,	 
 PM_RC_FAIL , // General Failure	 
 PM_RC_ALREADY_EXISTS // Exit function since required target alrteady exists	 
 } PM_ReturnCodeE;

typedef void ( *PM_CallbackFuncDDRstateT ) ( BOOL b_DDR_ready ) ;
typedef unsigned long long UINT64 ;
typedef unsigned long TimeIn32KhzUnit ;
typedef void ( *TickCallbackPtr ) ( UINT32 ) ;
typedef TimeIn32KhzUnit ( *SuspendCallbackPtr ) ( void ) ;
typedef void ( *PrepareTimeCallbackPtr ) ( void ) ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_NOT_ASSIGNED = -1 ,	 
	 
 GPIO_PIN_0 = 0 , GPIO_PIN_1 , GPIO_PIN_2 , GPIO_PIN_3 , GPIO_PIN_4 , GPIO_PIN_5 , GPIO_PIN_6 , GPIO_PIN_7 ,	 
	 
 GPIO_PIN_8 , GPIO_PIN_9 , GPIO_PIN_10 , GPIO_PIN_11 , GPIO_PIN_12 , GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 ,	 
 GPIO_PIN_16 , GPIO_PIN_17 , GPIO_PIN_18 , GPIO_PIN_19 , GPIO_PIN_20 , GPIO_PIN_21 , GPIO_PIN_22 , GPIO_PIN_23 ,	 
 GPIO_PIN_24 , GPIO_PIN_25 , GPIO_PIN_26 , GPIO_PIN_27 , GPIO_PIN_28 , GPIO_PIN_29 , GPIO_PIN_30 , GPIO_PIN_31 ,	 
 GPIO_PIN_32 , GPIO_PIN_33 , GPIO_PIN_34 , GPIO_PIN_35 , GPIO_PIN_36 , GPIO_PIN_37 , GPIO_PIN_38 , GPIO_PIN_39 ,	 
	 
 GPIO_PIN_40 , GPIO_PIN_41 , GPIO_PIN_42 , GPIO_PIN_43 , GPIO_PIN_44 , GPIO_PIN_45 , GPIO_PIN_46 , GPIO_PIN_47 ,	 
 GPIO_PIN_48 , GPIO_PIN_49 , GPIO_PIN_50 , GPIO_PIN_51 , GPIO_PIN_52 , GPIO_PIN_53 , GPIO_PIN_54 , GPIO_PIN_55 ,	 
 GPIO_PIN_56 , GPIO_PIN_57 , GPIO_PIN_58 , GPIO_PIN_59 , GPIO_PIN_60 , GPIO_PIN_61 , GPIO_PIN_62 , GPIO_PIN_63 ,	 
	 
 GPIO_PIN_64 , GPIO_PIN_65 , GPIO_PIN_66 , GPIO_PIN_67 , GPIO_PIN_68 , GPIO_PIN_69 , GPIO_PIN_70 , GPIO_PIN_71 ,	 
 GPIO_PIN_72 , GPIO_PIN_73 , GPIO_PIN_74 , GPIO_PIN_75 , GPIO_PIN_76 , GPIO_PIN_77 , GPIO_PIN_78 , GPIO_PIN_79 ,	 
 GPIO_PIN_80 , GPIO_PIN_81 , GPIO_PIN_82 , GPIO_PIN_83 , GPIO_PIN_84 , GPIO_PIN_85 , GPIO_PIN_86 , GPIO_PIN_87 ,	 
 GPIO_PIN_88 , GPIO_PIN_89 , GPIO_PIN_90 , GPIO_PIN_91 , GPIO_PIN_92 , GPIO_PIN_93 , GPIO_PIN_94 , GPIO_PIN_95 ,	 
	 
 GPIO_PIN_96 , GPIO_PIN_97 , GPIO_PIN_98 , GPIO_PIN_99 , GPIO_PIN_100 , GPIO_PIN_101 , GPIO_PIN_102 , GPIO_PIN_103 ,	 
 GPIO_PIN_104 , GPIO_PIN_105 , GPIO_PIN_106 , GPIO_PIN_107 , GPIO_PIN_108 , GPIO_PIN_109 , GPIO_PIN_110 , GPIO_PIN_111 ,	 
 GPIO_PIN_112 , GPIO_PIN_113 , GPIO_PIN_114 , GPIO_PIN_115 , GPIO_PIN_116 , GPIO_PIN_117 , GPIO_PIN_118 , GPIO_PIN_119 ,	 
 GPIO_PIN_120 , GPIO_PIN_121 , GPIO_PIN_122 , GPIO_PIN_123 , GPIO_PIN_124 , GPIO_PIN_125 , GPIO_PIN_126 , GPIO_PIN_127 ,	 
	 
 GPIO_MAX_AMOUNT_OF_PINS	 
 } GPIO_PinNumbers;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_RC_OK = 1 ,	 
	 
 GPIO_RC_INVALID_PORT_HANDLE = -100 ,	 
 GPIO_RC_NOT_OUTPUT_PORT ,	 
 GPIO_RC_NO_TIMER ,	 
 GPIO_RC_NO_FREE_HANDLE ,	 
 GPIO_RC_AMOUNT_OUT_OF_RANGE ,	 
 GPIO_RC_INCORRECT_PORT_SIZE ,	 
 GPIO_RC_PORT_NOT_ON_ONE_REG ,	 
 GPIO_RC_INVALID_PIN_NUM ,	 
 GPIO_RC_PIN_USED_IN_PORT ,	 
 GPIO_RC_PIN_NOT_FREE ,	 
 GPIO_RC_PIN_NOT_LOCKED ,	 
 GPIO_RC_NULL_POINTER ,	 
 GPIO_RC_PULLED_AND_OUTPUT ,	 
 GPIO_RC_INCORRECT_PORT_TYPE ,	 
 GPIO_RC_INCORRECT_TRANSITION_TYPE ,	 
 GPIO_RC_INCORRECT_DEBOUNCE ,	 
 GPIO_RC_INCORRECT_DIRECTION ,	 
 GPIO_RC_INCORRECT_INIT_VALUE	 
	 
 , GPIO_RC_INTC_ERROR ,	 
 GPIO_RC_PRM_ERROR	 
	 
 } GPIO_ReturnCode;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INPUT_PIN = 1 ,	 
 GPIO_OUTPUT_PIN	 
 } GPIO_PinDirection;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PIN_FREE_FOR_USE = 0 ,	 
 GPIO_PIN_USE_IN_PORT ,	 
 GPIO_PIN_USE_IN_INTERRUPT ,	 
 GPIO_PIN_USE_IN_PORT_WITH_INTERRUPT ,	 
 GPIO_PIN_LOCKED	 
 } GPIO_PinUsage;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinUsage pinUsage ;	 
 GPIO_PinDirection direction ;	 
 } GPIO_PinStatus;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_INITIAL_VALUE_NO_CHANGE = 0 ,	 
 GPIO_INITIAL_VALUE_LOW ,	 
 GPIO_INITIAL_VALUE_HIGH	 
 } GPIO_BitInitialValue;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 GPIO_PULL_UP_DOWN_DISABLE = 0 ,	 
 GPIO_PULL_UP_ENABLE ,	 
 GPIO_PULL_DOWN_ENABLE	 
 } GPIO_PullUpDown;

//ICAT EXPORTED STRUCT 
 typedef struct 
 {	 
 GPIO_PinNumbers pinNumber ;	 
 GPIO_PinDirection direction ;	 
 GPIO_TransitionType transitionType ;	 
 GPIO_Debounce debounce ;	 
 GPIO_PullUpDown pullUpDown ;	 
 GPIO_BitInitialValue initialValue ;	 
 } GPIO_PinConfiguration;

typedef UINT8 GPIO_PortHandle ;
typedef void ( *GPIO_ISR ) ( void ) ;
typedef UINT32 INTC_InterruptPriorityTable [ MAX_INTERRUPT_CONTROLLER_SOURCES ] ;
typedef UINT32 INTC_InterruptInfo ;
typedef void ( *INTC_ISR ) ( INTC_InterruptInfo interruptInfo ) ;
typedef void ( *PMCNotifyEventFunc ) ( UINT64 eventRegs ) ;
typedef void ( *PMCGetStatusNotifyFunc ) ( UINT16 status ) ;
typedef void ( *PMCReadCallback ) ( UINT8 *dataBuffPtr , UINT16 dataSize , UINT16 userId ) ;
typedef void ( *PMCWriteCallback ) ( UINT16 dataBuffPtr ) ;
typedef void ( *PMCGetGPADCValueNotifyFunc ) ( PMC_adc_reg_t reg , UINT16 value ) ;
typedef void ( * ReadingCallback ) ( int ) ;
typedef void ( * LTETempReadingCallback ) ( unsigned short , unsigned short ) ;
typedef void ( * ReadingCallbackBoth ) ( BOOL , int , int ) ;
typedef union
 {
 UINT8 autoControl ;
 UINT8 autoControl2 ;
 UINT8 manControl ;
 } adcModeCntrl_t ;
typedef union
 {
 UINT64 all ;
 Registers_ts regs ;
 } PMCEvents ;
//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 SHD_POWER_DOWN ,	 
 SHD_RESET ,	 
 SHD_GHOST ,	 
 SHD_SW_ERROR /* EEHandler triggered the reset */	 
 } ShutDownType_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RR_NORMAL_POWER_ON = 0x00 , // default , not combined with others	 
 RR_WATCH_DOG_TIMEOUT = 0x01 ,	 
 RR_SOFTWARE_GENERATED = 0x02 ,	 
 RR_CHARGING_BATTERY = 0x04 ,	 
 RR_LOW_BATTERY = 0x08 ,	 
 RR_ALARM_POWER_ON = 0x10 ,	 
 RR_EXT_POWER_ON = 0x20	 
 } 
 StartupReason_te;

//ICAT EXPORTED ENUM 
 typedef enum 
 {	 
 RE_RTC_ALARM = 0x01	 
 } StartupExtInd_te;

typedef BOOL ( *DiagPSisRunningFn ) ( void ) ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

DIAG_FILTER ( MIFI , AWS , Error , DIAG_INFORMATION)  
 diagPrintf ( " [ %s ] %s " , __FUNCTION__ , log_buffer );

//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\mbedtls_utils.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\standard\\corePKCS11\\source\\dependency\\3rdparty\\mbedtls_utils\\mbedtls_utils.c
typedef unsigned int size_t ;
typedef int mbedtls_iso_c_forbids_empty_translation_units ;
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef int32_t mbedtls_mpi_sint ;
typedef uint32_t mbedtls_mpi_uint ;
typedef uint64_t mbedtls_t_udbl ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef va_list __gnuc_va_list ;
typedef INT ssize_t ;
typedef ULONG pthread_t ;
typedef UINT pthread_key_t ;
typedef void ( *destructor_func_t ) ( void* ) ;
typedef ULONG mode_t ;
typedef sem_t *SEM_ID ;
typedef void mbedtls_ecp_restart_ctx ;
typedef mbedtls_ecp_keypair mbedtls_ecdsa_context ;
typedef void mbedtls_ecdsa_restart_ctx ;
typedef void mbedtls_pk_restart_ctx ;
typedef int ( *mbedtls_pk_rsa_alt_decrypt_func ) ( void *ctx , int mode , size_t *olen ,
 const unsigned char *input , unsigned char *output ,
 size_t output_max_len ) ;
typedef int ( *mbedtls_pk_rsa_alt_sign_func ) ( void *ctx ,
 int ( *f_rng ) ( void * , unsigned char * , size_t ) , void *p_rng ,
 int mode , mbedtls_md_type_t md_alg , unsigned int hashlen ,
 const unsigned char *hash , unsigned char *sig ) ;
typedef size_t ( *mbedtls_pk_rsa_alt_key_len_func ) ( void *ctx ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\threading.ppp
//PPL Source File Name : \\mbtk\\mbedTLS\\mbedTLS_2_1_8\\library\\threading.c
typedef int mbedtls_iso_c_forbids_empty_translation_units ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
typedef unsigned int size_t ;
typedef char CHAR ;
typedef unsigned char UCHAR ;
typedef int INT ;
typedef unsigned int UINT ;
typedef long LONG ;
typedef unsigned long ULONG ;
typedef short SHORT ;
typedef unsigned short USHORT ;
typedef unsigned int size_t ;
typedef unsigned int clock_t ;
typedef unsigned int time_t ;
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
typedef void * timer_t ;
typedef uint32_t clockid_t ;
typedef uint64_t tick_t ;
typedef uint32_t useconds_t ;
typedef va_list __gnuc_va_list ;
typedef INT ssize_t ;
typedef ULONG pthread_t ;
typedef UINT pthread_key_t ;
typedef void ( *destructor_func_t ) ( void* ) ;
typedef ULONG mode_t ;
typedef sem_t *SEM_ID ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cborparser.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\3rdparty\\tinycbor\\src\\cborparser.c
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef unsigned int size_t ;
typedef uint64_t CborTag ;
typedef CborError ( *CborStreamFunction ) ( void *token , const char *fmt , ... )

 __attribute__ ( ( __format__ ( printf , 2 , 3 ) ) )

 ;
typedef float float_t ;
typedef double double_t ;
typedef uintptr_t ( *IterateFunction ) ( char * , const uint8_t * , size_t ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cborencoder.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\3rdparty\\tinycbor\\src\\cborencoder.c
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef unsigned int size_t ;
typedef uint64_t CborTag ;
typedef CborError ( *CborStreamFunction ) ( void *token , const char *fmt , ... )

 __attribute__ ( ( __format__ ( printf , 2 , 3 ) ) )

 ;
typedef float float_t ;
typedef double double_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef int ( *__heapprt ) ( void * , char const * , ... ) ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cborpretty.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\3rdparty\\tinycbor\\src\\cborpretty.c
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef unsigned int size_t ;
typedef uint64_t CborTag ;
typedef CborError ( *CborStreamFunction ) ( void *token , const char *fmt , ... )

 __attribute__ ( ( __format__ ( printf , 2 , 3 ) ) )

 ;
typedef float float_t ;
typedef double double_t ;
typedef unsigned short wchar_t ;
//PPC Version : V2.1.9.30
//PPL Source File Name : \tavor\Arbel\obj_PMD2NONE\prepass_results\cborerrorstrings.ppp
//PPL Source File Name : \\mbtk\\amazon\\aws-iot-device-sdk-embedded-C\\libraries\\3rdparty\\tinycbor\\src\\cborerrorstrings.c
typedef signed int ptrdiff_t ;
typedef unsigned int size_t ;
typedef unsigned short wchar_t ;
typedef long double max_align_t ;
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
typedef unsigned int size_t ;
typedef uint64_t CborTag ;
typedef CborError ( *CborStreamFunction ) ( void *token , const char *fmt , ... )

 __attribute__ ( ( __format__ ( printf , 2 , 3 ) ) )

 ;
