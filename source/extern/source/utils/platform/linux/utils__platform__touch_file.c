#include <stdio.h>


int utils__platform__touch_file (const char *file_name)
{

	int rc;
	FILE *f;

	f = fopen (file_name, "rb");
	if (f == NULL)
	{
		f = fopen (file_name, "wb");
		if (f == NULL)
		{
			return -10;
		}
	}

	rc = fclose(f);
	if (rc != 0)
	{
		return -20;
	}


	return 0;

}


