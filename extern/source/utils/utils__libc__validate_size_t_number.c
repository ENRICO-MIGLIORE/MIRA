#include <stdio.h>
#include <stddef.h>


/*
 *
 *
 * Example when size_t is 8 bytes:
 *
 *  "0"                       ok
 *  "   0"                    ok
 *  "9876"                    ok
 *  "    1968"                ok
 *  "+9876"                   ok
 *  "    +1234"               ok
 *  "18446744073709551615"    ok
 *  "+18446744073709551615"   ok
 *
 *  ""                        error
 *  "   "                     error
 *  "-9876"                   error
 *  "98.76"                   error
 *  "18446744073709551616"    error
 *  "+18446744073709551616"   error
 *  "+0"                      error
 * 
 * 
 * 
 * Example when size_t is 4 bytes:
 *
 *  "0"             ok
 *  "   0"          ok
 *  "9876"          ok
 *  "    1968"      ok
 *  "+9876"         ok
 *  "    +1234"     ok
 *  "4294967295"    ok
 *  "+4294967295"   ok
 *
 *  ""              error
 *  "   "           error
 *  "-9876"         error
 *  "98.76"         error
 *  "4294967296"    error
 *  "+4294967296"   error
 *  "+0"            error

 */



int utils__libc__validate_size_t_number(const char* buffer, size_t buffer_len)
{
	size_t i;
	size_t j;
	size_t offset;
	size_t size;
	size_t residual_len_max;
	size_t residual_len;
	char* max;
	int done;
	int flag;


	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}

	size = sizeof(size_t);
	if (size == 4)
	{
		/*
		 * (2 ^ 32 - 1) = "4294967295" they are 10 digits
		 */
		max = "4294967295";
		residual_len_max = 10;
	}
	else if (size == 8)
	{
		/*
		 * (2 ^ 64 - 1) = "18446744073709551615" they are 20 digits
		 */
		max = "18446744073709551615";
		residual_len_max = 20;
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


	flag = 0;
	if (buffer[offset] == '+')
	{		
		offset++;
		flag = 1;
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
	residual_len = (size_t) buffer_len - offset;

	if (residual_len > residual_len_max)
	{
		return -600;
	}


	/*
	 * test if we exceed the maximum integer: 18446744073709551615 or 4294967295
	 */
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


	return 0;
}




#if 0

#include <string.h>

int test__utils__libc__validate_size_t_number(void)
{
	int rc;
	size_t i;
	char* good[] = { "0", "   0", "9876", "    1968", "+9876", "    +1234", "18446744073709551615", "+18446744073709551615",  " 18446744073709551615",  "  18446744073709551615",  " +18446744073709551615",  "  +18446744073709551615"     };
	size_t size;
	char* bad[] = { "", " ", "  ", "-1968", "12.34", "+0", "12hello34", "18446744073709551616", "+18446744073709551616",  " 18446744073709551616",  "  18446744073709551616",  " +18446744073709551616",  "  +18446744073709551616" };


	size = sizeof(good) / sizeof(char*);

	for (i = 0; i < size; i++)
	{
		rc = utils__libc__validate_size_t_number(good[i], strlen(good[i]));
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
		rc = utils__libc__validate_size_t_number(bad[i], strlen(bad[i]));
		if (rc == 0)
		{
			return -2000;
		}
	}

	return 0;

}

#endif
