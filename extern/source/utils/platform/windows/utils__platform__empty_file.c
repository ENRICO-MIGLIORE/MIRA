#include <stdio.h>

/*
 * If file doesn't exist, this function returns an error
 */

int utils__platform__empty_file (const char *file_name)
{
	FILE *f;

	f = fopen(file_name, "rb");
	if (f == NULL)
	{
		return -10;
	}

	fclose (f);

	f = fopen(file_name, "wb");
	if (f == NULL)
	{
		return -20;
	}

	fclose (f);

	return 0;
}



