#include "utils__libc.h"


int utils__libc__atoi (const char* buffer, size_t buffer_len, int* number)
{
	int rc;
	size_t i;
	size_t offset;
	int total;
	int digit;


	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}

	if (number == NULL)
	{
		return -300;
	}

	rc = utils__libc__validate_int_number(buffer, buffer_len);
	if (rc != 0)
	{
		return -400;
	}


	offset = 0;
	if (buffer[0] == '+')
	{
		offset = 1;
	}

	total = 0;

	for (i = offset; i < buffer_len; i++)
	{
		if ((buffer[i] >= '0') && (buffer[i] <= '9'))
		{
			digit = (int)(buffer[i] - '0');
			total = total * 10;
			total += digit;
		}
		else
		{
			return -500;
		}
	}

	*number = total;

	return 0;

}

