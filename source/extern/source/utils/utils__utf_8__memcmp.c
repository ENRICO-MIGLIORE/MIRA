#include <stdio.h>
#include <stddef.h>


int utils__utf_8__memcmp (const void *buffer_1, const void *buffer_2, size_t buffer_len, int uppercase_flag)
{
	size_t i;
	char *p_1;
	char *p_2;

	char a;
	char b;


	if (buffer_1 == NULL)
	{
		return -100;
	}

	if (buffer_2 == NULL)
	{
		return -200;
	}

	if (buffer_len == 0)
	{
		return -300;
	}

	p_1 = (char *) buffer_1;
	p_2 = (char *)  buffer_2;


	for (i = 0; i < buffer_len; i++)
	{
		if (uppercase_flag == 1)
		{
			a = p_1[i];
			b = p_2[i];

			if ((a >= 'a') && (a <= 'z'))
			{
				a -= 32;
			}
			
			if ((b >= 'a') && (b <= 'z'))
			{
				b -= 32;
			}
			
			if (a != b)
			{
				return -400;
			}
		}
		else
		{
			if (p_1[i] != p_2[i])
			{
				return -500;
			}
			
		}
	}

	return 0;
}


