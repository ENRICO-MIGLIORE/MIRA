#include <stdio.h>
#include <stddef.h>
#include <string.h>



int utils__libc__itoa (int n, char *buffer, size_t buffer_size, size_t *buffer_len)
{

	char buf[64];
	size_t len;


	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == NULL)
	{
		return -200;
	}

	sprintf(buf, "%d", n);

	len = strlen(buf);

	if (len + 1 > buffer_size)
	{
		return -300;
	}

	strcpy(buffer, buf);

	*buffer_len = len;

	return 0;
}
