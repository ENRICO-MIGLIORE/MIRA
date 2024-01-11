#include <stdio.h>


int utils__platform__create_directory (const char *dir_path)
{
	int rc;

	if (dir_path == NULL)
	{
		return -10;
	}

#if 0
	rc = _mkdir(dir_path);
	if (rc != 0)
	{
		return -20;
	}
#endif

	return 0;

}


