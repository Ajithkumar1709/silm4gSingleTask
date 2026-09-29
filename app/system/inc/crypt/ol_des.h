#ifndef _OL_DES_API_H_
#define _OL_DES_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MBTK_DES_KEY_SIZE		(8)
#define MBTK_DES_ENCRYPT     1
#define MBTK_DES_DECRYPT     0

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des_init
 * DESCRIPTION 
 *          This API is use to des init. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        !NULL:pointer des context struct
 *				NULL:error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void *ol_des_init( void );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des_free
 * DESCRIPTION 
 *          This API is use to des free. 
 * PARAMETERS 
 *        ctx    [IN]: pointer des context struct
 * RETURN VALUES
 *         NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_des_free( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des3_init
 * DESCRIPTION 
 *          This API is use to init des3. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        !NULL:pointer des3 context struct
 *				NULL:error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void *ol_des3_init( void );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des3_free
 * DESCRIPTION 
 *          This API is use to des3 free. 
 * PARAMETERS 
 *        ctx    [IN]: pointer des3 context struct
 * RETURN VALUES
 *         NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_des3_free( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des_setkey_enc
 * DESCRIPTION 
 *          This API is use to des set key enc. 
 * PARAMETERS 
 *        ctx    [IN]: ctx
 *        key    [IN]: key
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_des_setkey_enc( void *ctx, const unsigned char key[MBTK_DES_KEY_SIZE]);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des3_set2key_enc
 * DESCRIPTION 
 *          This API is use to des3 set key enc. 
 * PARAMETERS 
 *        ctx    [IN]: ctx
 *        key    [IN]: key
 *        keylen  [IN]: key length,vaild value:MBTK_DES_KEY_SIZE*2 or MBTK_DES_KEY_SIZE
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_des3_setkey_enc( void *ctx,const unsigned char *key,unsigned int keylen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des_crypt_ecb
 * DESCRIPTION 
 *          This API is use to des crypt ecb. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 *        input    [IN]: input
 *        output   [IN]: output
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_des_crypt_ecb( void *ctx,const unsigned char *input,unsigned char *output);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_des3_crypt_ecb
 * DESCRIPTION 
 *          This API is use to des3 crypt ecb. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 *        input    [IN]: input
 *        output   [IN]: output
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_des3_crypt_ecb( void *ctx,const unsigned char *input,unsigned char *output);

#ifdef __cplusplus
}
#endif

#endif
