#include <stdlib.h>
#include <string.h>
#include <stddef.h>

  


char utils__base_64__encoding_table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	                                       'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	                                       'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	                                       'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	                                       'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	                                       'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	                                       'w', 'x', 'y', 'z', '0', '1', '2', '3',
	                                       '4', '5', '6', '7', '8', '9', '+', '/'};




const size_t utils__base_64__mod_table[3] = {0, 2, 1};




int utils__base_64__encode (unsigned char *destination, size_t destination_size, size_t *destination_len, const unsigned char *source, size_t source_len)
{
	size_t i;
	size_t j;
	size_t len;
	size_t octet_a;
	size_t octet_b;
	size_t octet_c;
	size_t triple;
	
	len = 4 * ((source_len + 2) / 3);

	if (len > destination_size)
	{
		return -10;
	}

	j = 0;
	for (i = 0; i < source_len;) 
	{

		/*
		 * octet_a = i < source_len ? (unsigned char)source[i++] : 0;
		 * octet_b = i < source_len ? (unsigned char)source[i++] : 0;
		 * octet_c = i < source_len ? (unsigned char)source[i++] : 0;
		 */

		/* 
		 * octet_a = i < source_len ? (unsigned char) source[i++] : 0;
		 */
		if (i < source_len)
		{
			//octet_a = (unsigned char) source[i];
			octet_a = (size_t) source[i];
			i++;
		}
		else
		{
			octet_a = 0;
		}		

		/* 
		 * octet_b = i < source_len ? (unsigned char) source[i++] : 0;
		 */
		if (i < source_len)
		{
			//octet_b = (unsigned char) source[i];
			octet_b = (size_t) source[i];
			i++;
		}
		else
		{
			octet_b = 0;
		}	


		/* 
		 * octet_c = i < source_len ? (unsigned char) source[i++] : 0;
		 */
		if (i < source_len)
		{
			//octet_c = (unsigned char) source[i];
			octet_c = (size_t) source[i];
			i++;
		}
		else
		{
			octet_c = 0;
		}	


		triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		/*
		 * destination[j++] = base_64__encoding_table[(triple >> 3 * 6) & 0x3F];
		 * destination[j++] = base_64__encoding_table[(triple >> 2 * 6) & 0x3F];
		 * destination[j++] = base_64__encoding_table[(triple >> 1 * 6) & 0x3F];
		 * destination[j++] = base_64__encoding_table[(triple >> 0 * 6) & 0x3F];
		 */
		
		destination[j] = utils__base_64__encoding_table[(triple >> 18) & 0x3F];
		j++;

		destination[j] = utils__base_64__encoding_table[(triple >> 12) & 0x3F];
		j++;


		destination[j] = utils__base_64__encoding_table[(triple >> 6) & 0x3F];
		j++;

		
		destination[j] = utils__base_64__encoding_table[(triple) & 0x3F];
		j++;

	}

	for (i = 0; i < utils__base_64__mod_table[source_len % 3]; i++)
	{
		destination[len - 1 - i] = '=';
		
	}

	*destination_len = len;

	return 0;
}





#if 0

int base_64__encode (unsigned char *destination, size_t destination_size, size_t *destination_len, const unsigned char *source, size_t source_len)
{
	size_t i;
	size_t j;
	size_t dest_len;
	size_t octet_a;
	size_t octet_b;
	size_t octet_c;
	size_t triple;


	dest_len = 4 * ((source_len + 2) / 3);

	if (dest_len > destination_size)
	{
		return -10;
	}

	*destination_len = dest_len;

	j = 0;
	for (i = 0; i < source_len;) 
	{

		octet_a = i < source_len ? (unsigned char)source[i++] : 0;
		octet_b = i < source_len ? (unsigned char)source[i++] : 0;
		octet_c = i < source_len ? (unsigned char)source[i++] : 0;

		triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		//destination[j++] = base_64__encoding_table[(triple >> 3 * 6) & 0x3F];
		//destination[j++] = base_64__encoding_table[(triple >> 2 * 6) & 0x3F];
		//destination[j++] = base_64__encoding_table[(triple >> 1 * 6) & 0x3F];
		//destination[j++] = base_64__encoding_table[(triple >> 0 * 6) & 0x3F];


		//destination[j] = base_64__encoding_table[(triple >> 3 * 6) & 0x3F];
		destination[j] = base_64__encoding_table[(triple >> 18) & 0x3F];
		//destination[j] = base_64__encoding_table[(tmp * 6) & 0x3F];
		j++;


		//destination[j] = base_64__encoding_table[(triple >> 2 * 6) & 0x3F];
		destination[j] = base_64__encoding_table[(triple >> 12) & 0x3F];
		//destination[j] = base_64__encoding_table[(tmp * 6) & 0x3F];
		j++;


		//destination[j] = base_64__encoding_table[(triple >> 1 * 6) & 0x3F];
		destination[j] = base_64__encoding_table[(triple >> 6) & 0x3F];
		//destination[j] = base_64__encoding_table[(tmp * 6) & 0x3F];
		j++;


		//destination[j] = base_64__encoding_table[(triple >> 0 * 6) & 0x3F];
		destination[j] = base_64__encoding_table[(triple) & 0x3F];
		//destination[j] = base_64__encoding_table[(tmp * 6) & 0x3F];
		j++;

	}

	for (i = 0; i < base_64__mod_table[source_len % 3]; i++)
	{
		destination[*destination_len - 1 - i] = '=';
	}

	return 0;
}




void base_64__init(void);
static char *decoding_table = NULL;





unsigned char *utils__base_64__decode (const char *data, size_t input_length, size_t *output_length) 
{
	unsigned char *decoded_data;
	size_t sextet_a;
	size_t sextet_b;
	size_t sextet_c;
	size_t sextet_d;
	size_t triple;
	size_t i;
	size_t j;

	if (decoding_table == NULL) base_64__init();

	if (input_length % 4 != 0)
	{
		return NULL;
	}

	*output_length = input_length / 4 * 3;

	if (data[input_length - 1] == '=') (*output_length)--;
	if (data[input_length - 2] == '=') (*output_length)--;

	decoded_data = (unsigned char *) malloc(*output_length);

	if (decoded_data == NULL) 
	{
		return NULL;
    }

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


#endif
//
//void base_64__init (void) 
//{
//	int i;
//
//	decoding_table = (char *) malloc(256);
//
//	for (i = 0; i < 64; i++)
//	{
//		decoding_table[(unsigned char) utils__base_64__encoding_table[i]] = (char) i;
//	}
//
//	for (i = 0; i < 64; i++)
//	{
//		decoding_table_2[(unsigned char) utils__base_64__encoding_table[i]] = (char) i;
//	}
//}
//
//
//void base64_cleanup (void) 
//{
//	free(decoding_table);
//}



#if 0
void build_decoding_table(void);
static char *decoding_table = NULL;


unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length) 
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
 
 
void base64_cleanup (void) 
{
    free(decoding_table);
}
#endif
