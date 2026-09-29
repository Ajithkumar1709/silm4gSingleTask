#ifndef _OL_HMAC_API_H_
#define _OL_HMAC_API_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MBTK_MD_NONE=0,    		/**< None. */
    MBTK_MD_MD2,       			/**< The MD2 message digest. */
    MBTK_MD_MD4,       			/**< The MD4 message digest. */
    MBTK_MD_MD5,       			/**< The MD5 message digest. */
    MBTK_MD_SHA1,      			/**< The SHA-1 message digest. */
    MBTK_MD_SHA224,    		/**< The SHA-224 message digest. */
    MBTK_MD_SHA256,    		/**< The SHA-256 message digest. */
    MBTK_MD_SHA384,    		/**< The SHA-384 message digest. */
    MBTK_MD_SHA512,    		/**< The SHA-512 message digest. */
    MBTK_MD_RIPEMD160, 	/**< The RIPEMD-160 message digest. */
} mbtk_md_type_t;

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_new
 * DESCRIPTION 
 *          This API is use to create a hamc ctx. 
 * PARAMETERS 
 *        	NONE
 * RETURN VALUES
 *         !NULL: successful
 *         NULL: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void *ol_md_hmac_new(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_starts
 * DESCRIPTION 
 *          This API is use to md hmac starts. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 *				type		 [IN]: type
 *        key      [IN]: key
 *        keylen   [IN]: keylen
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md_hmac_starts( void *ctx, unsigned int type,const unsigned char *key, unsigned int keylen );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_update
 * DESCRIPTION 
 *          This API is use to md hmac update. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 *        input    [IN]: input
 *        ilen     [IN]: ilen
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md_hmac_update( void *ctx, const unsigned char *input, unsigned int ilen );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_finish
 * DESCRIPTION 
 *          This API is use to md hmac finish. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 *        output   [IN]: output
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md_hmac_finish( void *ctx, unsigned char *output );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_reset
 * DESCRIPTION 
 *          This API is use to md hmac reset. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md_hmac_reset( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md_hmac_free
 * DESCRIPTION 
 *          This API is use to relase the ctx created by ol_md_hmac_new. 
 * PARAMETERS 
 *        ctx      [IN]: ctx
 * RETURN VALUES
 *        NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_md_hmac_free( void*ctx );

#ifdef __cplusplus
}
#endif

#endif