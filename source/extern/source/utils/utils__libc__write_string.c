#include "utils__sdb.h"


int utils__libc__write_string (char* buffer, size_t buffer_size, const char* value, size_t value_len)
{

	if (buffer == NULL)
	{
		return -100;
	}

	if (value == NULL)
	{
		return -300;
	}

	if (value_len == 0)
	{
		return -500;
	}

	if (buffer_size == 0)
	{
		return -700;
	}

	if (value_len > buffer_size)
	{
		return -800;
	}

	memcpy(buffer, value, value_len);
	buffer[value_len] = '\0';

	return 0;

}

