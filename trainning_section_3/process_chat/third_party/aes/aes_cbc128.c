#include <string.h>
#include <stdio.h>

#include "aes_cbc128.h"
#include "aes.h"

struct AES_ctx m_ctx;

void add_padding_PKCS7(uint8_t *p_buff, size_t size_buff, size_t len)
{
	uint8_t pad = (AES_CBC128_BLOCKLEN) - (len%(AES_CBC128_BLOCKLEN));
	uint8_t * p_index = p_buff + len;
	memset(p_index, pad, (size_buff - len));
}

void remove_padding_PKCS7(uint8_t *p_buff, size_t *p_size)
{
	uint8_t pad = p_buff[(*p_size)-1];
	uint8_t *p_index = &p_buff[(*p_size) - pad];

	memset(p_index, 0, pad);
	(*p_size) = (*p_size) - pad;
}

uint32_t aes_cbc128_init(uint8_t *key, uint8_t *iv)
{
	if( (NULL == key) || (NULL == iv) )
		return AES_ERROR_NULL;
	memset(&m_ctx, 0 , sizeof(struct AES_ctx));
	AES_init_ctx_iv(&m_ctx, key, iv);
	return AES_SUCCESS;
}

uint32_t aes_cbc128_encrypt(uint8_t *p_data_in, size_t size_in, uint8_t *p_data_out, size_t *p_size_out)
{
	size_t size_out;
	
	if( (NULL == p_data_in) || (NULL == p_data_out) || (NULL == p_size_out) )
		return AES_ERROR_NULL;
	
	//* size calculation
	size_out = size_in + AES_CBC128_BLOCKLEN;
	size_out /= AES_CBC128_BLOCKLEN;
	size_out *= AES_CBC128_BLOCKLEN;
	
	if( size_out > (*p_size_out) )
		return AES_ERROR_SIZE;
	
	//* add padding to buffer
	memcpy(p_data_out, p_data_in, size_in);
	add_padding_PKCS7(p_data_out, size_out, size_in);
	
	//* AES encrypt
	AES_CBC_encrypt_buffer(&m_ctx, p_data_out, size_out);
	
	(*p_size_out) = size_out;
	return AES_SUCCESS;
}

uint32_t aes_cbc128_decrypt(uint8_t *p_data_in, size_t size_in, uint8_t *p_data_out, size_t *p_size_out)
{
	if( (NULL == p_data_in) || (NULL == p_data_out) || (NULL == p_size_out) )
		return AES_ERROR_NULL;
	
	memcpy(p_data_out, p_data_in, size_in);
	(*p_size_out) = size_in;
	
	AES_CBC_decrypt_buffer(&m_ctx, p_data_out, (*p_size_out));
	remove_padding_PKCS7(p_data_out, p_size_out);
	
	return AES_SUCCESS;
}
