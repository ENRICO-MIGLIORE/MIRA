#include <stdio.h>
#include <string.h>


/*
 *  Input:
 *
 *  path = "/home/user/my-path"
 *  file_name = "test.txt"
 *  path_separator = '/'
 *  
 *
 *  Output: "/home/user/my-path/test.txt"
 *  
 */


int utils__platform_build_fully_qualified_file_name (char *buffer, unsigned long buffer_size, unsigned long *buffer_len, const char *path, const char *file_name)
{
	unsigned long path_len;
	unsigned long file_name_len;
	unsigned long total_len;
	unsigned long safety_extra_room;
	unsigned long len;
	char path_separator; 

	if (path == NULL)
	{
		return -10;
	}

	if (file_name == NULL)
	{
		return -20;
	}

	if (buffer == NULL)
	{
		return -30;
	}

	if (buffer_size == 0)
	{
		return -40;
	}

	path_len = strlen(path);

	file_name_len = strlen(file_name);

	safety_extra_room = 4;

	total_len = path_len + file_name_len + safety_extra_room;
	if (total_len >= buffer_size)
	{
		return -50;
	}

	len = path_len;

	memcpy(buffer, path, len);

	path_separator = '/';

	if (buffer[len - 1] != path_separator)
	{
		buffer[len] = path_separator;
		len++;
	}

	memcpy(&buffer[len], file_name, file_name_len);
	len += file_name_len;
	buffer[len] = '\0';

	*buffer_len = len;

	return 0;

}

