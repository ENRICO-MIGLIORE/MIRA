#include "utils__libc.h"


int utils__libc__atoul(const char* buffer, size_t buffer_len, unsigned long* number)
{
	int rc;
	size_t i;
	size_t offset;
	unsigned long total;
	unsigned long digit;


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

	rc = utils__libc__validate_unsigned_long_number(buffer, buffer_len);
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
			digit = (unsigned long) (buffer[i] - '0');
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



#if 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int utils__libc__atoul__using_strtoul(const char* buffer, size_t buffer_len, unsigned long* number)
{

	char buf[64];
	unsigned long n;
	char* p;


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

	if (buffer_len + 1 > sizeof(buf))
	{
		return -400;
	}

	memcpy(buf, buffer, buffer_len);
	buf[buffer_len] = '\0';

	/*
	 *  if no valid conversion could be performed, a zero value is returned
	 *
	 *  if the value read is out of the range of representable values by an unsigned long int,
	 *  the function returns ULONG_MAX (defined in <limits.h>), and errno is set to ERANGE.
	 */
	n = strtoul(buf, &p, 10);

	if (errno == ERANGE)
	{
		return -500;
	}


	*number = n;

	return 0;

}
#endif
