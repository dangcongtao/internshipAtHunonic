#ifndef AES_CBC_128_H
#define AES_CBC_128_H

#include <stdint.h>
#include <stdlib.h>

#define AES_CBC128_BLOCKLEN	(16)

enum
{
	AES_SUCCESS,
	AES_ERROR_NULL,
	AES_ERROR_SIZE,
}aes_error_code_t;

/*(
 *
 *	[in]	key: 	buffer key must be size 16
 *	[in]	iv: 	buffer key must be size 16
 *
 *	return :
 *			AES_SUCCESS
 *			AES_ERROR_NULL
 */
uint32_t aes_cbc128_init(uint8_t *key, uint8_t *iv);

/**
 *
 *	[in]		p_data_in:
 *	[in]		size_in:
 *	[out]		p_data_out:
 *	[in,out]	p_size_out:
 *					[in]:	size of p_data_out
 *					[out]:	len of data out
 *	return :
 *			AES_SUCCESS
 *			AES_ERROR_NULL
 *			AES_ERROR_SIZE
 */
uint32_t aes_cbc128_encrypt(uint8_t *p_data_in, size_t size_in, uint8_t *p_data_out, size_t *p_size_out);

/**
 *
 *	[in]		p_data_in:
 *	[in]		size_in:
 *	[out]		p_data_out:
 *	[in,out]	p_size_out:
 *					[in]:	size of p_data_out
 *					[out]:	len of data out
 *	return :
 *			AES_SUCCESS
 *			AES_ERROR_NULL
 *			AES_ERROR_SIZE
 */
uint32_t aes_cbc128_decrypt(uint8_t *p_data_in, size_t size_in, uint8_t *p_data_out, size_t *p_size_out);

#endif //AES_CBC_128_H
