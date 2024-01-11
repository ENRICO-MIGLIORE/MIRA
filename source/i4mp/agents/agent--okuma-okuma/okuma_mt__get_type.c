#include "okuma_mt__private.h"


int okuma_mt__get_type (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;


	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);


	if ((rc == 0) && (om->machine_count > 0))
	{
		pthread_mutex_lock(&om->thread_mutex);

		strcpy(buffer, om->machine[md].config.type);

		pthread_mutex_unlock(&om->thread_mutex);

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