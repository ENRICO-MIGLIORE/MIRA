#include <stdio.h>
#include <stddef.h>


int utils__libc__validate_int_number (const char* buffer, size_t buffer_len)
{
	size_t i;
	size_t j;
	size_t offset;
	size_t size;
	size_t residual_len_max;
	size_t residual_len;
	size_t buf_len;
	char* max;
	char* min;
	int done;
	int flag;
	int sign;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}

	size = sizeof(int);
	if (size == 1)
	{
		/*
		 * (2^7 - 1) = "127" they are 3 digits
		 */
		max = "127";
		min = "128";
		residual_len_max = 3;
	}
	else if (size == 2)
	{
		/*
		 * (2^15 - 1) = "32767" they are 5 digits
		 */
		max = "32767";
		min = "32768";
		residual_len_max = 5;
	}
	else if (size == 4)
	{
		/*
		 * (2^31 - 1) = "2147483647" they are 10 digits
		 */
		max = "2147483647";
		min = "2147483648";
		residual_len_max = 10;
	}
	else if (size == 8)
	{
		/*
		 * (2^63 - 1) = "9223372036854775807" they are 19 digits
		 */
		max = "9223372036854775807";
		min = "9223372036854775808";
		residual_len_max = 19;
	}
	else
	{
		return -300;
	}


	done = 0;
	offset = 0;
	for (i = 0; (i < buffer_len) && (done == 0); i++)
	{
		if (buffer[i] == ' ')
		{
			offset++;
		}
		else
		{
			done = 1;
		}
	}

	sign = 0;
	flag = 0;
	if (buffer[offset] == '+')
	{
		offset++;
		flag = 1;		
	}
	else if (buffer[offset] == '-')
	{
		offset++;
		flag = 1;
		sign = 1;
	}


	if (offset >= buffer_len)
	{
		return -400;
	}

	if ((flag == 1) && (buffer[offset] == '0'))
	{
		/*
		 * "+0" is an error
		 */
		return -450;
	}

	for (i = offset; i < buffer_len; i++)
	{
		if ((buffer[i] < '0') || (buffer[i] > '9'))
		{
			return -500;
		}
	}


	/*
	 * if we get here, buffer_len is certainly greater than offset
	 */
	buf_len =  buffer_len;
	residual_len = (size_t) (buffer_len - offset);

	if (residual_len > residual_len_max)
	{
		return -600;
	}


	/*
	 * test if we exceed the maximum integer 4294967295
	 */

	if (sign == 0)
	{
		if (residual_len == residual_len_max)
		{
			j = 0;
			for (i = offset; i < buffer_len; i++)
			{
				if (buffer[i] > max[j])
				{
					return -700;
				}
				j++;
			}
		}
	}
	else
	{
		if (residual_len == residual_len_max)
		{
			j = 0;
			for (i = offset; i < buffer_len; i++)
			{
				if (buffer[i] > min[j])
				{
					return -800;
				}
				j++;
			}
		}

	}


	return 0;
}




#if 0

#include <string.h>

int test__utils__libc__validate_unsigned_long_number(void)
{
	int rc;
	size_t i;
	char* good[] = { "0", "   0", "9876", "    1968", "+9876", "    +1234", "4294967295", "+4294967295",  " 4294967295",  "  4294967295",  " +4294967295",  "  +4294967295" };
	size_t size;
	char* bad[] = { "", " ", "  ", "-1968", "12.34", "+0", "12hello34", "4294967296", "+4294967296",  " 4294967296",  "  4294967296",  " +4294967296",  "  +4294967296" };


	size = sizeof(good) / sizeof(char*);

	for (i = 0; i < size; i++)
	{
		rc = utils__libc__validate_unsigned_long_number(good[i], strlen(good[i]));
		if (rc != 0)
		{
			return -1000;
		}
	}


	size = sizeof(bad) / sizeof(char*);

	for (i = 0; i < size; i++)
	{
		if (i == 5)
		{
			int a;

			a = 1;
		}
		rc = utils__libc__validate_unsigned_long_number(bad[i], strlen(bad[i]));
		if (rc == 0)
		{
			return -2000;
		}
	}

	return 0;

}


#endif