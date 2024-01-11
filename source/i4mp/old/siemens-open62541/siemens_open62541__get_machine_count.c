#include "siemens_open62541__private.h"


int siemens_open62541__get_machine_count (char* buffer, size_t buffer_size, size_t* buffer_len)
{
	int len;
	size_t buffer_size_min;
	int rc;
	int md;


	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	md = 0;

	rc = siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return rc;
	}


	pthread_mutex_lock(&so->pthread_mutex);

	len = sprintf(buffer, "%d", so->machine_count);

	if (len <= 0)
	{
		rc = -5000;
	}
	else
	{
		*buffer_len = strlen(buffer);
	}

	pthread_mutex_unlock(&so->pthread_mutex);

	
	return rc;
}
