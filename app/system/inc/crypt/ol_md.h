#ifndef MBEDTLS_MD5_H
#define MBEDTLS_MD5_H


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md5_init
 * DESCRIPTION 
 *          This API is use to create a MD5 context. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        !NULL:pointer MD5 context struct
 *				NULL:error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void *ol_md5_init( void );

 /*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md5_free
 * DESCRIPTION 
 *          This API is use to releas and clear the MD5 context. 
 * PARAMETERS 
 *        ctx    [IN]: pointer MD5 context struct
 * RETURN VALUES
 *        NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_md5_free( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md5_starts
 * DESCRIPTION 
 *          This API is use to setup the MD5 context. 
 * PARAMETERS 
 *        ctx     [IN]: pointer MD5 context struct
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md5_starts( void *ctx );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md5_update
 * DESCRIPTION 
 *          This API is use to process the MD5 buffer. 
 * PARAMETERS 
 *        ctx     [IN]: pointer MD5 context struct
 *        input   [IN]: buffer holding the data
 *        ilen    [IN]: length of the input data
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md5_update( void *ctx, const unsigned char *input,unsigned int ilen );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_md5_finish
 * DESCRIPTION 
 *          This API is use to finish the MD5 digest
 * PARAMETERS 
 *        ctx     [IN]: pointer MD5 context struct
 *        output  [OUT]: MD5 checksum result
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_md5_finish( void *ctx, unsigned char output[16] );

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_md5.h */
