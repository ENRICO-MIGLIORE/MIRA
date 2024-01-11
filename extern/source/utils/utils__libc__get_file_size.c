#include <stdio.h>
#include <stddef.h>


int utils__libc__get_file_size (const char* file_name, size_t* file_size)
{

	FILE* f;
	long size;
	int sizeof_long;
	int sizeof_size_t;


	if (file_name == NULL)
	{
		return -100;
	}

	if (file_size == NULL)
	{
		return -200;
	}

	f = fopen(file_name, "rb");
	if (f == NULL)
	{
		return -300;
	}

	fseek(f, 0, SEEK_END);     /* Get the file length, allocate the data and read */

	size = ftell(f);

	fclose(f);


	if (size < 0)
	{
		return -400;
	}

	*file_size = (size_t) size;	

	sizeof_long = sizeof(long);
	sizeof_size_t = sizeof(size_t);

	if (sizeof_long > sizeof_size_t)
	{
		return 1;
	}


	return 0;
}
