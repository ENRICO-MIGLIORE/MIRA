#include "utils__libc.h"



int utils__libc__write_double (double* data, const char* value, size_t value_len)
{
	int rc;
	double tmp;

	if (data == NULL)
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

	rc = utils__libc__atod(value, value_len, &tmp);
	if (rc != 0)
	{
		return -700;
	}

	*data = tmp;

	return 0;

}
