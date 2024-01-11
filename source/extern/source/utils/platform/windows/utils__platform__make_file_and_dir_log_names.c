#include <stdio.h>
#include <string.h>
#include <stddef.h>


int utils__platform__make_file_and_dir_log_names (const char *dir_path, const char *name_prefix, const char *name, const char *name_separator, char *file_name, size_t file_name_size, size_t *file_name_len, size_t number, const char *file_extension)
{
	char id_buf[256];
	size_t id_buf_len;
	int n;
	size_t path_len;
	size_t name_len;
	size_t max_len;
	size_t room;
	const char *path_separator;

	if (dir_path == NULL)
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

	n = (int) number;


	id_buf_len = sprintf (id_buf, "%d", n);

	path_len = strlen(dir_path);
	name_len = strlen(name);

	/*
	 * Example:  "path\FGGR--NAME--2019--1.txt"
	 *
	 *   FGGR = name_prefix
	 *   --   = name_separator
	 *   NAME = name
	 *   1    = numb
	 *   file_extension = txt
	 */
	room = 15;
	max_len = path_len + name_len + id_buf_len + room;
	if (max_len >= file_name_size)
	{
		return -70;
	}

	 path_separator = "\\";                     /* Windows */

	strcpy (file_name, dir_path);
	strcat (file_name, path_separator);
	strcat (file_name, name_prefix);
	strcat (file_name, name_separator);
	strcat (file_name, name);
	strcat (file_name, name_separator);
	strcat (file_name, id_buf);
	strcat (file_name, file_extension);

	*file_name_len = strlen(file_name);


	return 0;
}



