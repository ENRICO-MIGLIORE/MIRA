#include <stdio.h>
#include <stddef.h>


int utils__percent_encoding__decode__data (char *buffer, size_t buffer_len, size_t *buffer_new_len)
{

	size_t i;
	size_t j;
	int end;
	unsigned char *b;
	unsigned char high;
	unsigned char low;


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
				return -30;
			}

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
				return -40;
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
				return -50;
			}


			high = high << 4;
			high &= 0xF0;

			b[j] = (unsigned char) (high | low);

			j++;
			i += 3;
		}
		else
		{
			b[j] = b[i];
			j++;
			i++;
		}

		if (i >= buffer_len)
		{
			end = 1;
		}
	} 
	while (end == 0);

	*buffer_new_len = j;

	if (*buffer_new_len > buffer_len)
	{
		return -100;
	}

	return 0;

}




