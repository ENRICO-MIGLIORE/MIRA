#include <stdio.h>
#include <stddef.h>



/*
* RFC 3986 states:
*
* Reserved (must arrive encoded)
*
*  ':' 	   '/' 	  '?'  	 '#' 	'[' 	']' 	'@' 	'!' 	'$' 	'&' 	"'" 	'(' 	')' 	'*' 	'+' 	',' 	';' 	'=' 	'%' 	' '
*  %3A     %2F 	  %3F 	 %23 	%5B 	%5D 	%40 	%21 	%24 	%26 	%27 	%28 	%29 	%2A 	%2B 	%2C 	%3B 	%3D 	%25 	%20 or +
*
*
*
*
* Unreserved (must arrive unencoded)
*
*
*  'a', 'b', ...'z'        'A', 'B',...'Z'        '0', '1',   ,'9'    '-'  '.'  '_'   '~'
*
*
*
* Other characters must be percent encoded
*
*  0x00, 0x01, '\r'                       0xFF
*
*/

#define  TABLE_MAX      256

static const unsigned char utils__percent_encoding__ascii_table[TABLE_MAX] = { '\0', 1, 2, 3, 4, 5, 6, 7, 8, 9, '\n', 11, 12, '\r', 14, 15, 16,
	                                                                           17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, ' ', 
	                                                                           '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0',
	                                                                           '1','2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 
	                                                                           'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
	                                                                           'Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`',
	                                                                           'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
	                                                                           'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{','|','}','~', 127, 128,
																			   129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
																			   145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
																			   161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
																			   177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
																			   193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
																			   209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
																			   225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
																			   241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

static const unsigned char utils__percent_encoding_encode_table[TABLE_MAX] = {'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e', 
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','u','u','e',
	                                                                          'u','u','u','u','u','u','u','u','u','u','e','e','e','e','e','e', 
	                                                                          'e','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u', 
	                                                                          'u','u','u','u','u','u','u','u','u','u','u','e','e','e','e','u', 
	                                                                          'e','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u', 
	                                                                          'u','u','u','u','u','u','u','u','u','u','u','e','e','e','u','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e',
	                                                                          'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'};
	                                                                          


int utils__percent_encoding__decode_data_strict (char *buffer, size_t buffer_len, size_t *buffer_new_len)
{

	size_t i;
	size_t j;
	int end;
	unsigned char *b;
	unsigned char c;
	unsigned char high;
	unsigned char low;
	unsigned char index;

	if (buffer == NULL)
	{
		return -10;
	}

	if (buffer_new_len == NULL)
	{
		return -20;
	}

	if (buffer_len == 0)
	{
		*buffer_new_len = 0;
		return 0;
	}

	b = (unsigned char *) buffer;


	


	end = 0;
	i = 0;
	j = 0;
	do 
	{



		if (b[i] == '%')
		{
			if (i + 2 >= buffer_len)
			{
				return -100;
			}

			//if (!(((b[i + 1] >= '0') && (b[i + 1] <= '9')) || ((b[i + 1] >= 'A') && (b[i + 1] <= 'F'))))
			//{
			//	return -110;
			//}

			//if (!(((b[i + 2] >= '0') && (b[i + 2] <= '9')) || ((b[i + 2] >= 'A') && (b[i + 2] <= 'F'))))
			//{
			//	return -120;
			//}


			if ((b[i + 1] >= '0') && (b[i + 1] <= '9'))
			{
				high = b[i + 1] - '0';
			}
			else if ((b[i + 1] >= 'A') && (b[i + 1] <= 'F'))
			{
				high = b[i + 1] - 'A' + 10;
			}
			else
			{
				return -110;
			}

			if ((b[i + 2] >= '0') && (b[i + 2] <= '9'))
			{
				low = b[i + 2] - '0';
			}
			else if ((b[i + 2] >= 'A') && (b[i + 2] <= 'F'))
			{
				low = b[i + 2] - 'A' + 10;
			}
			else
			{
				return -120;
			}

			high = high << 4;
			high &= 0xF0;

			b[j] = (unsigned char) (high | low);

			index = b[j];

			if (utils__percent_encoding_encode_table[index] == 'u')
			{
				return -130;
			}

			j++;
			i += 3;
		}
		else
		{

			if (b[i] == '+')
			{
				b[j] = ' ';
				j++;
				i++;
			}
			else
			{
				c = b[i];

				index = c;

				if (utils__percent_encoding_encode_table[index] == 'e')
				{
					return -140;
				}

				b[j] = c;
				j++;
				i++;
			}
		}

		if (i >= buffer_len)
		{
			end = 1;
		}
	} 
	while (end == 0);


	*buffer_new_len = j;

	return 0;

}
