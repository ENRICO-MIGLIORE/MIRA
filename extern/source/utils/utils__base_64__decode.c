#include <stdlib.h>
#include <string.h>
#include <stddef.h>
  

extern char utils__base_64__encoding_table[64];


static char utils__base_64__decoding_table[256];
static int utils__base_64__decoding_table_status = 0;


int utils__base_64__decode (unsigned char *destination, size_t destination_size, size_t *destination_len, const char *source, size_t source_len) 
{
	
	size_t sextet_a;
	size_t sextet_b;
	size_t sextet_c;
	size_t sextet_d;
	size_t triple;
	size_t i;
	size_t j;
	unsigned char *p;

	if (utils__base_64__decoding_table_status != 1) 
	{
		/*
		 * Build the decoding table at the very first call of this function
		 */

		p = (unsigned char *) &utils__base_64__encoding_table[0];

		for (i = 0; i < 64; i++)
		{
			
			utils__base_64__decoding_table[p[i]] = (char) i;
		}

		utils__base_64__decoding_table_status = 1;

    }

	if (source_len % 4 != 0)
	{
		return -10;
	}

	*destination_len = source_len / 4 * 3;

	if (source[source_len - 1] == '=') (*destination_len)--;
	if (source[source_len - 2] == '=') (*destination_len)--;


	//decoded_data = (unsigned char *) malloc(*output_length);
	//decoded_data = destination;

	//if (decoded_data == NULL) 
	//{
	//	return NULL;
 //   }

	j = 0;
	for (i = 0; i < source_len;) 
	{

		sextet_a = source[i] == '=' ? 0 & i++ : utils__base_64__decoding_table[source[i++]];
		sextet_b = source[i] == '=' ? 0 & i++ : utils__base_64__decoding_table[source[i++]];
		sextet_c = source[i] == '=' ? 0 & i++ : utils__base_64__decoding_table[source[i++]];
		sextet_d = source[i] == '=' ? 0 & i++ : utils__base_64__decoding_table[source[i++]];

		triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

		if (j < *destination_len) destination[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *destination_len) destination[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *destination_len) destination[j++] = (triple >> 0 * 8) & 0xFF;
	}

	return 0;
}


#if 0


void base64_cleanup (void) 
{
	free(decoding_table);
}

void build_decoding_table(void);
static char *decoding_table = NULL;


unsigned char *utils__base_64__decode (const char *data, size_t input_length, size_t *output_length) 
{
    unsigned char *decoded_data;
	uint32_t sextet_a;
	uint32_t sextet_b;
	uint32_t sextet_c;
	uint32_t sextet_d;
	uint32_t triple;
	int i;
	int j;

    if (decoding_table == NULL) build_decoding_table();
 
    if (input_length % 4 != 0) return NULL;
 
    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
 
    decoded_data = (unsigned char *) malloc(*output_length);
    if (decoded_data == NULL) return NULL;
 
    for (i = 0, j = 0; i < input_length;) 
	{
 
        sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
 
        triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);
 
        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
 
    return decoded_data;
}
 
 
void build_decoding_table (void) 
{
    int i;

    decoding_table = (char *) malloc(256);
 
    for (i = 0; i < 64; i++)
	{
        decoding_table[(unsigned char) encoding_table[i]] = i;
	}
}
 
 


#endif
