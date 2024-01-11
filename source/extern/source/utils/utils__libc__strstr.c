#include <stdio.h>
#include <stddef.h>

/*
 *
 *   "Ciao come stai bene?"          "stai"
 */

char *utils__libc__strstr (const char *buffer, size_t buffer_len, const char *buffer_2, size_t buffer_2_len)
{
		
	size_t i;
	size_t j;
	size_t match_len;
	int first_time;
	char *p;

	if (buffer == NULL)
	{
		return (char*)NULL;
	}

	if (buffer_2 == NULL)
	{
		return (char*)NULL;
	}

	if (buffer_2_len == 0) 
	{
	    return (char *) buffer;
	}

	if (buffer_2_len > buffer_len)
	{
		return (char *) NULL;
	}

				
	p = NULL;
	first_time = 0;
	match_len = 0;
	j = 0;

	for (i = 0; i < buffer_len; i++)
	{
		if (buffer[i] == buffer_2[j])
		{
			if (first_time == 0)
			{
				first_time = 1;
				p = (char *) &buffer[i];
			}

			j++;
			match_len++;
			if (match_len == buffer_2_len)
			{
				return p;
			}
		}
		else
		{
			first_time = 0;
			j = 0;
			match_len = 0;
		}
	}

	return (char *) NULL;
}



