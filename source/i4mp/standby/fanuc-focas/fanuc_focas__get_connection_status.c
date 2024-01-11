#include "fanuc_focas__private.h"


#define BUFFER_SIZE_MIN    32


int fanuc_focas__get_connection_status (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode)
{

	size_t fd;
	size_t buffer_size_min;
	int rc;

	mode = 0;  /* keep the msvc compiler happy */

	buffer_size_min = BUFFER_SIZE_MIN;

	rc = fanuc_focas__check_parameters(machine_id, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return -100;
	}

	fd = machine_id - 1;


	pthread_mutex_lock(&ff->pthread_mutex);


	if (ff->pthread_started != 1)
	{
		strcpy(buffer, "0");
	}
	else if (ff->machine[fd].connected == 1)
	{
		strcpy(buffer, "1");
	}
	else
	{
		strcpy(buffer, "0");
	}

	*buffer_len = 1;


	pthread_mutex_unlock(&ff->pthread_mutex);


	return rc;
}

