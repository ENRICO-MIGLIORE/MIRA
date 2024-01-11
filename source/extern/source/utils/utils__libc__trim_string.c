#include <stdio.h>
#include <stddef.h>


/*
 * This function removes all leading and trailing spaces.
 *
 * To remove leading spaces, it left shifts buffer into buffer itself
 *
 * Fully tested on 2020-12-16
 *
 *  buffer = "   CIAO      ERIKA   "         trimmed_buffer_len = 15    -->   buffer = "CIAO      ERIKA"
 *  buffer = "CIAO      ERIKA"               trimmed_buffer_len = 15    -->   buffer = "CIAO      ERIKA"
 *  buffer = "   CIAO      ERIKA"            trimmed_buffer_len = 15    -->   buffer = "CIAO      ERIKA"
 *  buffer = "CIAO      ERIKA    "           trimmed_buffer_len = 15    -->   buffer = "CIAO      ERIKA"
 *  buffer = "CIAO"                          trimmed_buffer_len = 4     -->   buffer = "CIAO"
 *  buffer = ""                              trimmed_buffer_len = 0
 *  buffer = " "                             trimmed_buffer_len = 0
 *  buffer = "  "                            trimmed_buffer_len = 0
 *  buffer = "A"                             trimmed_buffer_len = 1
 */


int utils__libc__trim_string (char *buffer, size_t buffer_len, size_t *buffer_new_len, char c)
{

	int state;
	int end;
	size_t i;
	size_t j;
	size_t k;

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


	i = 0;
	j = 0;
	end = 0;
	state = 0;

	do
	{
		switch (state)
		{
		case 0:
			if (buffer[i] != c)
			{
				buffer[0] = buffer[i];
				j = 1;
				state = 1;
			}
			break;

		case 1:
			buffer[j] = buffer[i];
			j++;
			break;
		}

		i++;
		if (i >= buffer_len)
		{
			end = 1;
		}
	}
	while (end == 0);

	
	k = j - 1;
	end = 0;
	do
	{
		if (buffer[k] == c)
		{

			if (k > 0)
			{
				k--;
			}
			else
			{
				return -30;
			}
		}
		else
		{
			end = 1;
		}
	}
	while (end == 0);


	*buffer_new_len = k + 1;

	if (*buffer_new_len > buffer_len)
	{
		return -40;
	}


	return 0;

}
