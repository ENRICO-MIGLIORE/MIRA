#include "utils__libc.h"


int utils__libc__write_1_or_0 (int* data, const char* value, size_t value_len)
{

	char buffer[8];
	char* p;
	int i;
	int rc;


	if (data == NULL)
	{
		return -100;
	}

	if (value == NULL)
	{
		return -200;
	}

	if (value_len == 0)
	{
		return -300;
	}

	p = (char*) value;

	for (i = 0; i < 3; i++)
	{
		buffer[i] = (char)toupper((int)(*p));
		p++;
	}

	rc = memcmp(buffer, "YES", 3);
	if (rc == 0)
	{
		*data = 1;  /* yes */
	}
	else
	{
		*data = 0;  /* no */
	}

	return 0;
}

