#include <stdio.h>
#include <string.h>
#include <stddef.h>

    
int utils__libc__validate_ipv4_address (const char *buffer, size_t buffer_len)
{
	size_t i;
	unsigned char c;
	unsigned char *n;
	size_t len;
	size_t digits;
	size_t bytes_consumed;
	unsigned char buf[24];

	if ((buffer_len < 7) || (buffer_len > 15))
	{
		return -100;
	}

	memcpy(buf, buffer, buffer_len);
	buf[buffer_len] = '\0';

	bytes_consumed = 0;
	digits = 0;

	n = buf;

	for (i = 0; i < 4; i++)
	{
		if (i < 3)
		{
			c = '.';
		}
		else
		{
			c = '\0';
		}
		
		if (n[1] == c)
		{

			if (bytes_consumed > buffer_len)
			{
				return -150;
			}

			/*
			 * Allowed: '0', '1', '2', ..., '9'
			 */
			if (!((n[0] >= '0') && (n[0] <= '9')))
			{
				return -200;
			}

			digits++;
			bytes_consumed += 2;
			len = 1;

		}
		else if (n[2] == c)
		{
			if (bytes_consumed >= buffer_len)
			{
				return -250;
			}

			/*
			 * Allowed: "10", "11", ..., "98", "99"
			 */
			if (!((n[0] >= '1') && (n[0] <= '9')))
			{
				return -300;
			}
			if (!((n[1] >= '0') && (n[1] <= '9')))
			{
				return -400;
			}

			digits++;
			bytes_consumed += 3;
			len = 2;

		}
		else if (n[3] == c)
		{
			if (bytes_consumed >= buffer_len)
			{
				return -450;
			}

			/*
			 * Allowed: "100", "101", ..., "154", "155", ..., "198", "199",
			 *          "200", "201", ..., "254", "255"
			 */

			if (n[0] == '1')
			{
				if (!((n[1] >= '0') && (n[1] <= '9')))
				{
					return -500;
				}
				if (!((n[2] >= '0') && (n[2] <= '9')))
				{
					return -600;
				}
			}
			else if (n[0] == '2')
			{
				if ((n[1] >= '0') && (n[1] <= '4'))
				{
					if (!((n[2] >= '0') && (n[2] <= '9')))
					{
						return -700;
					}
				}
				else if (n[1] == '5')
				{
					if (!((n[2] >= '0') && (n[2] <= '5')))
					{
						return -800;
					}
				}
				else
				{
					return -850;
				}
			}
			else
			{
				return -900;
			}

			digits++;
			bytes_consumed += 4;
			len = 3;

		}
		else
		{
			return -1000;
		}

		n += len + 1;

	}

	if (digits != 4)
	{
		return -200;
	}

	return 0;

}




