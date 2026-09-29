#ifndef _SIMCOM_AES_H_
#define _SIMCOM_AES_H_

#include <stddef.h>


int sAPI_AesEncrypt(const unsigned char *key, size_t key_len, const unsigned char *plaintext, unsigned char *ciphertext);
int sAPI_AesDecrypt(const unsigned char *key, size_t key_len, const unsigned char *ciphertext, unsigned char *plaintext);

#endif
