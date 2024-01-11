#include <stdio.h>


int utils__platform__does_file_exist (const char *file_name)
{
	
	FILE *f;

	f = fopen (file_name, "rb");
	if (f == NULL)
	{
		return -10;
	}

    fclose(f);

	return 0;

}


