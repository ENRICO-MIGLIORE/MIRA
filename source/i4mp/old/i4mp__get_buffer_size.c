#include "mira__private.h"


int i4mp__get_buffer_size (char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int len;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == NULL)
	{
		return -200;
	}

	if (buffer_size < 8)
	{
		return -300;
	}

	if (i4mp->started != 1)
	{
		return -400;
	}


	len = sprintf(buffer, "%zu", i4mp->buffer_size);

	if (len <= 0)
	{
		return -5000;
	}

	*buffer_len = strlen(buffer);


	return 0;
}



