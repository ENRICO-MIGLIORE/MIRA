#include <stdio.h>

int utils__platform__remove_file (const char *file_name)
{

	FILE *f;
	int rc;

	f = fopen(file_name, "rb");

	if (f == NULL)
	{
		return 0;
	}

	fclose(f);

	rc = remove(file_name);

	return rc;
}



