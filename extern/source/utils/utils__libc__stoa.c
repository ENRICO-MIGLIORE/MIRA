#include <stdio.h>
#include <stddef.h>
#include <string.h>



int utils__libc__stoa (short n, char *buffer, size_t buffer_size, size_t *buffer_len)
{
	char buf[64];
	size_t len;
	int m;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == NULL)
	{
		return -200;
	}

	m = (int) n;

	sprintf(buf, "%d", m);

	len = strlen(buf);

	if (len + 1 > buffer_size)
	{
		return -300;
	}

	strcpy(buffer, buf);

	*buffer_len = len;

	return 0;
}
