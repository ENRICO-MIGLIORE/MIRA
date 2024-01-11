#include <direct.h>
#include <string.h>



int utils__platform__create_directory_by_dir_name (char *dir_path, const char *dir_name)
{
	int rc;
	char *dir_path_separator;

    if (dir_path == NULL)
    {
		return -10;
	}

    if (dir_name == NULL)
    {
		return -20;
	}

	dir_path_separator = "\\";
	strcat (dir_path, dir_path_separator);
	strcat (dir_path, dir_name);

	rc = _mkdir(dir_path);
	if (rc != 0)
	{
		return -30;
	}

	return 0;

}

