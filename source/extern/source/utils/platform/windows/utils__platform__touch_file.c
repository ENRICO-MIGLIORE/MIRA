#include <stdio.h>


int utils__platform__touch_file (const char *file_name)
{
	
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

	fclose(f);

	return 0;

}


