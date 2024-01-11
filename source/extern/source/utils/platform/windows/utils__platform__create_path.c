#include <direct.h>
#include <string.h>


int utils__platform__create_path (const char *dir_path)
{
	int rc;

	if (dir_path == NULL)
	{
		return -10;
	}

	rc = _mkdir(dir_path);
	if (rc != 0)
	{
		return -20;
	}

	return 0;

}


