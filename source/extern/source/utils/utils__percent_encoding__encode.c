#include <string.h>
#include <stdio.h>
#include <stddef.h>

/*
 *  Example of forbidden characters: "*&"
 *
 */


int utils__percent_encoding__encode(const char *reserved_characters, const char *buffer_in, size_t buffer_in_len, char *buffer_out, size_t buffer_out_size, size_t *buffer_out_len)
{
	size_t i;
	size_t j;
	size_t len;
	size_t out_len;
	int flag;

	if (reserved_characters == NULL)
	{
		return -5;
	}

	if (buffer_in == NULL)
	{
		return -10;
	}

	if (buffer_out == NULL)
	{
		return -20;
	}

	if (buffer_out_len == NULL)
	{
		return -25;
	}

	if (buffer_out_size == 0)
	{
		return -30;
	}

	if (buffer_in_len == 0)
	{
		return -40;
	}

	len = strlen (reserved_characters);

	if (len == 0)
	{
		return -50;
	}


	out_len = 0;
	for (i = 0; i < buffer_in_len; i++)
	{
		flag = 0;

		for (j = 0; (j < len) && (flag == 0); j++)
		{
			if (buffer_in[i] == reserved_characters[j])
			{
				if (out_len + 3 > buffer_out_size)
				{
					return -60;
				}

				sprintf (&buffer_out[out_len], "%%%02X", reserved_characters[j]); 
				out_len += 3;

				flag = 1;
			}
		}

		if (flag == 0)
		{
			if (out_len > buffer_out_size)
			{
				return -70;
			}

			buffer_out[out_len] = buffer_in[i];
			out_len++;
		}
		
	}

	*buffer_out_len = out_len;

	return 0;
}


