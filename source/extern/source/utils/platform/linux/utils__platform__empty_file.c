#include <stdio.h>


int utils__platform__empty_file (const char *file_name)
{
	FILE *f;
	int rc;

	f = fopen(file_name, "wb");
	if (f == NULL)
	{
		return -10;
	}

	fclose (f);

	return 0;
}



