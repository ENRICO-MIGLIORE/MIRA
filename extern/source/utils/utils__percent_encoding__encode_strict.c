#include <string.h>
#include <stdio.h>
#include <stddef.h>


/*
 * A-Z
 * a-z
 * 0-9
 * - _ ~ .
 *
 */
int utils__percent_encoding__encode_strict (const char *buffer_in, size_t buffer_in_len, char *buffer_out, size_t buffer_out_size, size_t *buffer_out_len)
{
	size_t out_len;
	size_t i;

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



	out_len = 0;
	for (i = 0; i < buffer_in_len; i++)
	{
		if ((buffer_in[i] >= '0') && (buffer_in[i] <= '9'))
		{
			if (out_len > buffer_out_size)
			{
				return -70;
			}
	
			buffer_out[out_len] = buffer_in[i];
			out_len++;
		}
		else if ((buffer_in[i] >= 'A') && (buffer_in[i] <= 'Z'))
		{
			if (out_len > buffer_out_size)
			{
				return -70;
			}
	
			buffer_out[out_len] = buffer_in[i];
			out_len++;
		}
		else if ((buffer_in[i] >= 'a') && (buffer_in[i] <= 'z'))
		{
			if (out_len > buffer_out_size)
			{
				return -70;
			}
	
			buffer_out[out_len] = buffer_in[i];
			out_len++;
		}
		else if ((buffer_in[i] == '-') || (buffer_in[i] == '_')|| (buffer_in[i] == '~'))
		{
			if (out_len > buffer_out_size)
			{
				return -70;
			}
	
			buffer_out[out_len] = buffer_in[i];
			out_len++;
		}
		else
		{
			if (out_len + 3 > buffer_out_size)
			{
				return -60;
			}
	
			sprintf (&buffer_out[out_len], "%%%02X", buffer_in[i]); 
			out_len += 3;
		}
	}

	*buffer_out_len = out_len;


	return 0;
}

