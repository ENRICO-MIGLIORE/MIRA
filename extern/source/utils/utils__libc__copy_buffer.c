#include <stdio.h>
#include <string.h>
#include <stddef.h>


int utils__libc__copy_buffer (char *buffer, size_t buffer_size, size_t *buffer_len, char *buffer_2, size_t buffer_2_len)
{

	if (buffer_2_len > (buffer_size - 1))
	{
		return -10;
	}

	memcpy (buffer, buffer_2, buffer_2_len);

	*buffer_len = buffer_2_len;

	return 0;
}







