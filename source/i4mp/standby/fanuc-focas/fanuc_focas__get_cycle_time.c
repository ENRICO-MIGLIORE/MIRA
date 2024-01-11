#include "fanuc_focas__private.h"


#define BUFFER_SIZE_MIN    32


int fanuc_focas__get_cycle_time (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode)
{

	size_t fd;
	int rc;
	size_t buffer_size_min;


	buffer_size_min = BUFFER_SIZE_MIN;

	rc = fanuc_focas__check_parameters(machine_id, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return -100;
	}

	fd = machine_id - 1;
	rc = 0;


	pthread_mutex_lock(&ff->pthread_mutex);


	if (ff->machine[fd].connected == 0)
	{
		rc = -1000;
	}
	else if (ff->pthread_started != 1)
	{
		rc = -1100;
	}
	else if (ff->machine[fd].cycle_time_valid != 1)
	{
		rc = -1200;
	}


	if (rc == 0)
	{
		strcpy(buffer, ff->machine[fd].cycle_time_utf_8);
		*buffer_len = ff->machine[fd].cycle_time_utf_8_len;
	}
	else
	{
		if (mode == 0)
		{			
			strcpy(buffer, FANUC_FOCAS__CONFIG__INVALID_READ_RESPONSE_STRING);
			*buffer_len = strlen(FANUC_FOCAS__CONFIG__INVALID_READ_RESPONSE_STRING);
			rc = 0;
		}
	
	}


	pthread_mutex_unlock(&ff->pthread_mutex);


	return rc;
}





