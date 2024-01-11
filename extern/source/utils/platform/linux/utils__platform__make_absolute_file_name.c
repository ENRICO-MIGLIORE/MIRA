#include <stdio.h>
#include <string.h>


int utils__platform__make_absolute_file_name (const char *path, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension, char *file_name, unsigned long file_name_size, unsigned long *file_name_len)
{
	unsigned long path_len;
	unsigned long name_len;
	unsigned long max_len;
	unsigned long room;
	const char *path_separator; 

	if (path == NULL)
	{
		return -10;
	}

	if (name_prefix == NULL)
	{
		return -20;
	}

	if (name == NULL)
	{
		return -30;
	}

	if (name_separator == NULL)
	{
		return -40;
	}

	if (file_extension == NULL)
	{
		return -50;
	}

	if (file_name == NULL)
	{
		return -60;
	}

	path_len = strlen(path);
	name_len = strlen(name);

	room = 16;
	max_len = path_len + name_len + room;
	if (max_len >= file_name_size)
	{
		return -90;
	}

	path_separator = "/";

	strcpy (file_name, path);
	strcat (file_name, path_separator);
	strcat (file_name, name_prefix);
	strcat (file_name, name_separator);
	strcat (file_name, name);
	strcat (file_name, file_extension);

	*file_name_len = strlen(file_name);

	return 0;
}




