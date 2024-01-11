#include "fanuc_focas__private.h"


int fanuc_focas__get_type (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;

	buffer_size_min = FANUC_FOCAS__CONFIG__BUFFER_SIZE_256;

	rc = fanuc_focas__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if ((rc == 0) && (ff->machine_count > 0))
	{
		pthread_mutex_lock(&ff->thread_mutex);

		strcpy(buffer, ff->machine[md].config.type);

		pthread_mutex_unlock(&ff->thread_mutex);

		*buffer_len = strlen(buffer);
	}
	else
	{
		buffer[0] = '-';
		buffer[1] = '\0';
		*buffer_len = 1;
	}


	return 0;
}