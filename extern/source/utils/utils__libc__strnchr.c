#include <stdio.h>
#include <stddef.h>


char *utils__libc__strnchr (const char *buffer, size_t buffer_len, char c)
{
	size_t i;

	if (buffer == NULL)
	{
		return NULL;
	}

	if (buffer_len == 0)
	{
		return NULL;
	}


	for (i = 0; i < buffer_len; i++)
	{
		if (buffer[i] == c)
		{
			return (char *) &buffer[i];
		}
	}

	return NULL;

}


