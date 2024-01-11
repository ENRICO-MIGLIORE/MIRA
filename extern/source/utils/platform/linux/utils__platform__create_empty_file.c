#include <stdio.h>


int utils__platform__create_empty_file (const char *file_name)
{
	int rc;
	FILE *f;

	/*
	 * Create an empty file
	 */

	f = fopen(file_name, "wb");
	if (f == NULL)
	{
		return -10;
	}

	fclose(f);

	return 0;

}





