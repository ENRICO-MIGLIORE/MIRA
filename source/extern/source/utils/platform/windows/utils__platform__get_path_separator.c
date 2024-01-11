#include <stdio.h>
#include <string.h>


int utils__platform__get_path_separator (char *path_separator, size_t path_separator_size)
{

	if (path_separator == NULL)
	{
		return -10;
	}

	if (path_separator_size < 2)
	{
		return -30;
	}

	path_separator[0] = '\\';
	path_separator[1] = '\0';


	return 0;

}

