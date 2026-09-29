#include "mbtk_comm_api.h"
#include "ol_aes.h"
#include "ol_hmac.h"
#include "ol_des.h"
#include "menu_demo_api.h"


int aes_demo( void );
int hmac_demo( void );
int des_demo( void );
int md5_demo( void );

static demo_menu_info menu_info[] =
{
	{"aes test","",aes_demo,NULL},
	{"hmac test","",hmac_demo,NULL},
	{"des test","",des_demo,NULL},
	{"md5 test","",md5_demo,NULL}
};

demo_menu_info *crypto_demo_menu_info(unsigned int *num)
{
	*num = sizeof(menu_info)/sizeof(menu_info[0]);
	return menu_info;
}

static int crypt_cmp_buff(unsigned char *buf1,unsigned char *buf2,unsigned int cmplen)
{
	unsigned int i = 0;
	int ret = 0;

	for(i = 0; i< cmplen ;i++){
		op_uart_printf("cmp [%d] buf1:%x,buf2:%x\r\n",i,buf1[i], buf2[i]);
		if(buf1[i] != buf2[i]){
			ret = -1;
			break;
		}
	}
	return ret;
}

static int aes_demo_ecb_crypt_with_key(
					unsigned int mode,
				 	unsigned char* out, 
				 	const unsigned char* in, 
				 	unsigned int inlen,
          const unsigned char* key, 
          unsigned int keylen)
{
	void *ctx = NULL;
	memset(out,0x0,MBTK_AES_BLOCK_SIZE*4);
	
	ctx = ol_aes_init();
	if(!ctx)
		return -1;

	if(mode == MBTK_AES_ENCRYPT)
		ol_aes_setkey_enc(ctx,key, keylen);
	else
		ol_aes_setkey_dec(ctx,key, keylen);
	ol_aes_crypt_ecb(ctx,mode,in,out);
	ol_aes_free(ctx);

	return 0;
}

static int aes_demo_cbc_crypt_with_key(
					unsigned int mode,
				 	unsigned char* out, 
				 	const unsigned char* in, 
				 	unsigned int inlen,
          const unsigned char* key, 
          unsigned int keylen,
          const unsigned char* iv)
{
	void *ctx = NULL;
	memset(out,0x0,64);
	
	ctx = ol_aes_init();
	if(!ctx)
		return -1;

	if(mode == MBTK_AES_ENCRYPT)
		ol_aes_setkey_enc(ctx,key, keylen);
	else
		ol_aes_setkey_dec(ctx,key, keylen);
	ol_aes_crypt_cbc(ctx,mode,inlen,iv,in,out);
	ol_aes_free(ctx);

	return 0;
}


int aes_demo( void )
{
	unsigned char cipher[MBTK_AES_BLOCK_SIZE*4] = {0};
	unsigned char plain[MBTK_AES_BLOCK_SIZE*4] = {0};
	//AES ECB
	{
		static const byte niPlain[] =
		{
		    0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
		    0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a
		};

		static const byte niCipher[] =
		{
		    0xf3,0xee,0xd1,0xbd,0xb5,0xd2,0xa0,0x3c,
		    0x06,0x4b,0x5a,0x7e,0x3d,0xb1,0x81,0xf8
		};

		static const byte niKey[] =
		{
		    0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
		    0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
		    0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
		    0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4
		};

		memset(cipher, 0, MBTK_AES_BLOCK_SIZE*4);
    memset(plain, 0, MBTK_AES_BLOCK_SIZE*4);
		
		aes_demo_ecb_crypt_with_key(MBTK_AES_ENCRYPT,cipher,
			niPlain,sizeof(niPlain),niKey, sizeof(niKey));
		if(crypt_cmp_buff(cipher, niCipher,MBTK_AES_BLOCK_SIZE) != 0)
		{
			op_uart_printf("aes ecb fail at encrypt");
			return -1;
		}

		aes_demo_ecb_crypt_with_key(MBTK_AES_DECRYPT,plain,
			niCipher,sizeof(niCipher),niKey, sizeof(niKey));
	  if(crypt_cmp_buff(plain, niPlain,MBTK_AES_BLOCK_SIZE) != 0)
		{
			op_uart_printf("aes ecb fail at decrypt");
			return -1;
		}

	}

	//AES CBC
	{
    static const unsigned char msg[] = { /* "Now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    };
    unsigned char key[] = "0123456789abcdef   ";  /* align */
    unsigned char iv[] = "1234567890abcdef   ";  /* align */

    memset(cipher, 0, MBTK_AES_BLOCK_SIZE*4);
    memset(plain, 0, MBTK_AES_BLOCK_SIZE*4);
	
    aes_demo_cbc_crypt_with_key(MBTK_AES_ENCRYPT,cipher,
			msg,MBTK_AES_BLOCK_SIZE,key, MBTK_AES_BLOCK_SIZE,iv);
    aes_demo_cbc_crypt_with_key(MBTK_AES_DECRYPT,plain,
			cipher,MBTK_AES_BLOCK_SIZE,key, MBTK_AES_BLOCK_SIZE,iv);
		if(crypt_cmp_buff(plain,msg,MBTK_AES_BLOCK_SIZE) != 0)
		{
			op_uart_printf("aes cbc fail");
			return -1;
		}
	}
	return 0;
}


int des_demo(void)
{
	int ret = 0;
	int i = 0;
	void* ctx = NULL;
  void* ctx3 = NULL;
	unsigned char buf[8] = {0};
	const unsigned char *pskey = NULL;

	static const unsigned char des_in[] = {
		0x4E, 0x6F, 0x77, 0x20, 0x69, 0x73, 0x20, 0x74
	};
	
	static const unsigned char des_key[] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
	};
	
	static const unsigned char des_out[] = {
		0x6A, 0x2A, 0x19, 0xF4, 0x1E, 0xCA, 0x85, 0x4B
	};

	static const unsigned char des3_key[] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
  	0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01
 	};
	
	static const unsigned char des3_out[] = {
		0x03, 0xE6, 0x9F, 0x5B, 0xFA, 0x58, 0xEB, 0x42
	};

	memcpy( buf, des_in, 8 );
	pskey = des_key;
	
	ctx = ol_des_init();
	ol_des_setkey_enc( ctx, pskey );
	for(i = 0; i<10000;i++){
		ol_des_crypt_ecb( ctx, buf, buf);
	}
	ol_des_free(ctx);
	if(crypt_cmp_buff(buf,des_out,8) != 0)
	{
		ret = -1;
		op_uart_printf("des_demo at des-8 fail");
	}
	
	memcpy( buf, des_in, 8 );
	pskey = des3_key;
	
	ctx3 = ol_des3_init();
	ol_des3_setkey_enc( ctx3, pskey,MBTK_DES_KEY_SIZE*2 );
	for(i = 0; i<10000;i++){
		ol_des3_crypt_ecb( ctx3, buf, buf);
	}
	ol_des3_free(ctx3);
	if(crypt_cmp_buff(buf,des3_out,8) != 0)
	{
		ret = -1;
		op_uart_printf("des_demo at des-16 fail");
	
	}
		
  return ret;
}

int hmac_demo(void)
{
	int ret = 0;
	int i = 0;
	void* ctx;
	unsigned char outbuf[64];
	const unsigned char hmac_in[] = {"are you ok"};
	const unsigned char hmac_key[] = {"no"};
	const unsigned char hmac_out[] = {
	0x64, 0x77, 0xe1, 0xa9, 0xa9, 0xcc, 0xc1, 0xd5, 0xc8, 0x7a,
	0xf6, 0x14, 0x6e, 0xdd, 0xde, 0xc6, 0xbe, 0x2e, 0xf5, 0xb2
	};
	
	const unsigned char *pskey = hmac_key;
	int keylen = strlen(pskey);
	const unsigned char *testin = hmac_in;
	int inlen = strlen(testin);
	int outlen = sizeof(hmac_out);

	ctx = ol_md_hmac_new();
	if(!ctx)
	{
		op_uart_printf("hmac ctx create fail");
		return -1;
	}
	ol_md_hmac_starts(ctx, MBTK_MD_SHA1,pskey, keylen);
	ol_md_hmac_update(ctx, testin,inlen);
	ol_md_hmac_finish(ctx, outbuf);
	if(crypt_cmp_buff(outbuf,hmac_out,outlen) != 0)
	{
		op_uart_printf("hmac_demo fail");
		ol_md_hmac_free(ctx);
		return -1;
	}
	
	ol_md_hmac_free(ctx);
	return ret;
}

int md5_demo( void )
{
	void *ctx = NULL;
	unsigned char md5sum[16] = {0};
	static const unsigned char md5_in[] =
	{
		"message digest" 
	};
		
	static const unsigned char md5_out[] =
	{ 
		0xF9, 0x6B, 0x69, 0x7D, 0x7C, 0xB7, 0x93, 0x8D,
		0x52, 0x5A, 0x2F, 0x31, 0xAA, 0xF1, 0x61, 0xD0 
	};

	ctx = ol_md5_init();
	if(!ctx)
	{
		op_uart_printf("md5 ctx create fail");
		return -1;
	}
	ol_md5_starts(ctx);
	ol_md5_update(ctx, md5_in, strlen(md5_in));
	ol_md5_finish(ctx, md5sum);
	if (crypt_cmp_buff(md5sum, md5_out, 16) != 0)
  {
		op_uart_printf("md5 fail");
		ol_md5_free(ctx);
		return -1;
	} 

	ol_md5_free(ctx);
  return 0;
}


