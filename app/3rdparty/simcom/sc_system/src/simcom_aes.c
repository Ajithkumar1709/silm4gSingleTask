#include "mbedtls/aes.h"

// AES encryption function
int sAPI_AesEncrypt(const unsigned char *key, size_t key_len, const unsigned char *plaintext, unsigned char *ciphertext)
{
    int ret = 0;
    mbedtls_aes_context aes_ctx;
    
    mbedtls_aes_init(&aes_ctx);
    ret = mbedtls_aes_setkey_enc(&aes_ctx, key, key_len * 8); // 8 bits per byte
    if( ret != 0 )
    {
        goto exit;
    }

    ret = mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_ENCRYPT, plaintext, ciphertext );
    if( ret != 0 )
    {
        goto exit;
    }
    
exit:
    mbedtls_aes_free( &aes_ctx );
    return ret;
}

// AES decryption function
int sAPI_AesDecrypt(const unsigned char *key, size_t key_len, const unsigned char *ciphertext, unsigned char *plaintext)
{
    int ret = 0;
    mbedtls_aes_context aes_ctx;
    
    mbedtls_aes_init(&aes_ctx);
    ret = mbedtls_aes_setkey_dec(&aes_ctx, key, key_len * 8); // 8 bits per byte
    if( ret != 0 )
    {
        goto exit;
    }

    ret = mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT, ciphertext, plaintext);
    if( ret != 0 )
    {
        goto exit;
    }

exit:
    mbedtls_aes_free( &aes_ctx );
    return ret;
}

