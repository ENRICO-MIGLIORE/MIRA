#include "siemens_open62541__private.h"


int siemens_open62541__get_buffer_size(char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int len;
	size_t size;

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

	size = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	len = sprintf(buffer, "%zu", size);

	if (len <= 0)
	{
		return -5000;
	}

	*buffer_len = strlen(buffer);


	return 0;
}