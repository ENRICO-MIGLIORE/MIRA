#include "utils__time.h"


int utils__time__get_iso_extended_time(char *buffer, size_t buffer_size, size_t *buffer_len)
{
	time_t current_time;
	struct tm *local_time;

	if (buffer == NULL)
	{
		return -10;
	}

	if (buffer_len == NULL)
	{
		return -20;
	}

	if (buffer_size < UTILS__TIME__BUFFER_SIZE)
	{
		return -30;
	}

	time(&current_time);

	local_time = localtime(&current_time);


	/*
	 * ISO extended format:  "23:15:58"
	 */
	*buffer_len = strftime (buffer, buffer_size, "%H:%M:%S", local_time);

	return 0;
}


