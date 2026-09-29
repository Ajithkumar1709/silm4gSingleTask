#ifndef _OL_AES_API_H
#define _OL_AES_API_H

#ifdef __cplusplus
extern "C" {
#endif

#define MBTK_AES_BLOCK_SIZE 16

#define MBTK_AES_ENCRYPT     1 /**< AES encryption. */
#define MBTK_AES_DECRYPT     0 /**< AES decryption. */

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_init
 * DESCRIPTION 
 *          This API is use to create a AES context. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        !NULL:pointer AES context struct
 *				NULL:error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void *ol_aes_init( void );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_free
 * DESCRIPTION 
 *          This API is use to releases and clears the specified AES context. 
 * PARAMETERS 
 *        ctx    [IN]: pointer AES context struct
 * RETURN VALUES
 *        NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_aes_free( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_setkey_enc
 * DESCRIPTION 
 *          This API is use to sets the encryption key. 
 * PARAMETERS 
 *        ctx     [IN]: pointer AES context struct
 *        key     [IN]: the encryption key.
 *        keylen  [IN]: The size of key len.
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_aes_setkey_enc( void *ctx, const unsigned char *key,
                    unsigned int keylen );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_setkey_dec
 * DESCRIPTION 
 *          This API is use to sets the decryption key. 
 * PARAMETERS 
 *        ctx     [IN]: pointer AES context struct
 *        key     [IN]: the decryption key.
 *        keylen  [IN]: The size of key len.
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_aes_setkey_dec( void *ctx, const unsigned char *key,
                    unsigned int keylen );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_crypt_ecb
 * DESCRIPTION 
 *          This API is use to performs an AES single-block encryption or decryption operation.
 * PARAMETERS 
 *        ctx     [IN]: pointer AES context struct
 *        mode    [IN]: the AES operation,MBTK_AES_ENCRYPT or MBTK_AES_DECRYPT
 *        input   [IN]: the buffer holding the input data
 *        output  [OUT]: the buffer where the output data will be written
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_aes_crypt_ecb( void *ctx,int mode,
                    const unsigned char input[16],
                    unsigned char output[16] );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_aes_crypt_cbc
 * DESCRIPTION 
 *          This API is use to performs an AES-CBC encryption or decryption operation on full blocks.
 * PARAMETERS 
 *        ctx     [IN]: pointer AES context struct
 *        mode    [IN]: the AES operation,MBTK_AES_ENCRYPT or MBTK_AES_DECRYPT
 *        length  [IN]: the length of the input data in Bytes.
 *        iv      [IN]: initialization vector
 *        input   [IN]: the buffer holding the input data
 *        output  [OUT]: the buffer where the output data will be written
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_aes_crypt_cbc( void *ctx,int mode,
                    size_t length,unsigned char iv[16],
                    const unsigned char *input,unsigned char *output );


#ifdef __cplusplus
}
#endif

#endif /* ol_aes.h */
