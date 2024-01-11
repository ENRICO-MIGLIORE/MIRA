#include <stdio.h>
#include <string.h>
#include <stddef.h>


static const char build_url_buffer__lookup_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


int utils__libc__build_url_buffer (char *buffer, size_t buffer_size, size_t *buffer_len, char **name, size_t *name_len, char **value, size_t *value_len, size_t pair_count, const char *forbidden_charset)
{
	size_t i;
	size_t j;
	size_t k;
	size_t charset_len;
	unsigned char low;
	unsigned char high;
	size_t len;
	int flag;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_size == 0)
	{
		return -200;
	}

	if (buffer_len == NULL)
	{
		return -300;
	}

	if (name == NULL)
	{
		return -400;
	}

	if (name_len == NULL)
	{
		return -500;
	}

	if (value == NULL)
	{
		return -600;
	}

	if (value_len == NULL)
	{
		return -700;
	}

	if (pair_count == 0)
	{
		return -800;
	}

	if (forbidden_charset == NULL)
	{
		return -900;
	}


	charset_len = strlen(forbidden_charset);

	len = 0;
	for (k = 0; k < pair_count; k++)
	{

		if (name_len[k] == 0)
		{
			return -1000;
		}

		if (name[k] == NULL)
		{
			return -1100;
		}

		for (i = 0; i < name_len[k]; i++)
		{
			if (len + 4 >= buffer_size)
			{
				return -1200;
			}


			flag = 0;
			for (j = 0; j < (charset_len) && (flag == 0); j++)
			{
				if (name[k][i] == forbidden_charset[j])
				{
					buffer[len] = '%';

					high = (unsigned char) (name[k][i] >> 4);
					high = (unsigned char) (high & 0x0F);
					buffer[len + 1] = build_url_buffer__lookup_table[high];

					low = (unsigned char) (name[k][i] & 0x0F);
					buffer[len + 2] = build_url_buffer__lookup_table[low];

					len += 3;

					flag = 1;
				}
			}

			if (flag == 0)
			{
				buffer[len] = name[k][i];
				len++;
			}
		}

		buffer[len] = '=';
		len++;

		if (value[k] == NULL)
		{
			return -1300;
		}

		for (i = 0; i < value_len[k]; i++)
		{
			if (len + 4 >= buffer_size)
			{
				return -1400;
			}

			flag = 0;
			for (j = 0; j < (charset_len) && (flag == 0); j++)
			{
				if (value[k][i] == forbidden_charset[j])
				{
					buffer[len] = '%';

					high = (unsigned char) (value[k][i] >> 4);
					high = (unsigned char) (high & 0x0F);
					buffer[len + 1] = build_url_buffer__lookup_table[high];

					low = (unsigned char) (value[k][i] & 0x0F);
					buffer[len + 2] = build_url_buffer__lookup_table[low];

					len += 3;

					flag = 1;
				}
			}

			if (flag == 0)
			{
				buffer[len] = value[k][i];
				len++;
			}
		}


		if (k < (pair_count - 1))
		{
			buffer[len] = '&';
			len++;
		}
	}

	*buffer_len = len;

	return 0;

}
