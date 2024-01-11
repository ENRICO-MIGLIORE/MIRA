#include <stdio.h>
#include <string.h>


/*
 *  Input:
 *
 *  path = "C:\Users\Admin\Desktop\PROGS\PROG-75--FGG\documentation\project-1\deployment-base\db\system"
 *  file_name = "test.txt"
 *  path_separator = '\'
 *  
 *
 *  Output:  C:\Users\Admin\Desktop\PROGS\PROG-75--FGG\documentation\project-1\deployment-base\db\system\test.txt
 *  
 */

int utils__platform__build_fully_qualified_file_name (char *buffer, size_t buffer_size, const char *path, const char *file_name)
{
	size_t path_len;
	size_t file_name_len;
	size_t total_len;
	size_t safety_extra_room;
	size_t len;
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

	path_separator = '\\';

	if (buffer[len - 1] != path_separator)
	{
		buffer[len] = path_separator;
		len++;
	}

	memcpy(&buffer[len], file_name, file_name_len);
	len += file_name_len;
	buffer[len] = '\0';


	return 0;

}

