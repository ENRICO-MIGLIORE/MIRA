#include <stdio.h>
#include <string.h>
#include <stddef.h>


static const unsigned char convert_utf8__lookup_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


/*
 *  buffer[64]
 *
 *  buffer[0] = 'C'
 *  buffer[1] = 'i'
 *  buffer[2] = 'a'
 *  buffer[3] = '0'
 *  buffer[4] = 0xE2
 *  buffer[5] = 0x80
 *  buffer[6] = 0xA2
 *  buffer[7] = '.'
 *
 *
 *  buffer[0] = 'C'
 *  buffer[1] = 'i'
 *  buffer[2] = 'a'
 *  buffer[3] = '0'
 *  buffer[4] = '%'
 *  buffer[5] = ''
 *  buffer[6] = ''
 *  buffer[7] = '%'
 *  buffer[8] = ''
 *  buffer[9] = ''
 *  buffer[10] = '%'
 *  buffer[11] = ''
 *  buffer[12] = ''
 *  buffer[13] = '.'
 */
int utils__libc__convert_utf8_data_to_percent_encoded_data (char *buffer, size_t buffer_len, size_t buffer_size_residual, size_t *buffer_new_len)
{
	size_t j;
	size_t i;
	int result;
	unsigned char tmp;
	unsigned char high;
	unsigned char low;
	size_t room;
	int index;
	size_t new_len_tmp;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}

	if (buffer_new_len == NULL)
	{
		return -300;
	}

	room = 3;
	new_len_tmp = buffer_len;
	index = 0;

	for (i = 0; i < buffer_len; i++)
	{
		result = buffer[index] & 0x80;    /*  1XXX XXXX           1000 0000   */

	    if (result == 0x80)
		{

			if (room > buffer_size_residual)
			{
				return -400;
			}
			/*
			 * shift ahead by 3
			 */
			for (j = new_len_tmp - 1; j > index; j--)
			{
				buffer[j + 2] = buffer[j];
			}

			tmp = (unsigned char) buffer[index];

			high = (unsigned char) (tmp >> 4);
			high = (unsigned char) (high & 0x0F);

			high = convert_utf8__lookup_table[high];

			low = (unsigned char) (tmp & 0x0F);
			low = convert_utf8__lookup_table[low];


			buffer[index] = '%';
			buffer[index + 1] = (char) high;
			buffer[index + 2] = (char) low;
			index += 3;

			if (buffer_size_residual < 2)
			{
			    return -500;
			}

			buffer_size_residual -= 2;
			new_len_tmp += 2;
		}
		else
		{
			index++;
		}
	}

	*buffer_new_len = new_len_tmp;

	return 0;

}

