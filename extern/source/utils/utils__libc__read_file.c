#include <stdio.h>
#include <stddef.h>


int utils__libc__read_file (const char* file_name, char* buffer, size_t buffer_size)
{

	FILE* f;
	size_t chunk_size;
	size_t count;
	size_t len;
	int done;


	if (file_name == NULL)
	{
		return -100;
	}

	if (buffer == NULL)
	{
		return -200;
	}

	if (buffer_size == 0)
	{
		return -300;
	}

	f = fopen(file_name, "rb");
	if (f == NULL)
	{
		return -400;
	}

	
	/*
	 * tune chunk_size
	 */

	chunk_size = 1;

	if (buffer_size > 64)
	{
		chunk_size = 64;
	}

	if (buffer_size > 128)
	{
		chunk_size = 128;
	}

	if (buffer_size > 256)
	{
		chunk_size = 256;
	}

	if (buffer_size > 512)
	{
		chunk_size = 512;
	}

	if (buffer_size > 1024)
	{
		chunk_size = 1024;
	}

	done = 0;
	len = 0;
	do
	{
		count = fread(&buffer[len], 1, chunk_size, f);
		if (count > 0)
		{
			len += count;
			if (len > buffer_size)
			{
				done = -10;
			}
			else if (len == buffer_size)
			{
				done = 1;
			}
		}
		else
		{
			done = 2;
		}
	} 
	while (done == 0);


	fclose(f);

	if (done < 0)
	{
		return -1000;
	}

	return 0;

}

