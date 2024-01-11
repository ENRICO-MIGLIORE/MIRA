#include "siemens_open62541__private.h"


int siemens_open62541__get_part_counter (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	rc = siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return rc;
	}



	pthread_mutex_lock(&so->pthread_mutex);

	if (so->machine[md].config.online == 0)
	{
		*buffer_len = 0;    /* part counter is not available because agent is not configured to connect to machine */
	}
	else if (so->machine[md].part_counter_valid != 1)
	{
		*buffer_len = 0;		
	}
	else
	{
		strcpy(buffer, so->machine[md].part_counter_utf_8);
		*buffer_len = so->machine[md].part_counter_utf_8_len;
	}

	pthread_mutex_unlock(&so->pthread_mutex);


	return 0;
}







