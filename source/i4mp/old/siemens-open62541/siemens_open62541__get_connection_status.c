#include "siemens_open62541__private.h"


int siemens_open62541__get_connection_status (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
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
		buffer[0] = '3';  		/* connection status not available because agent is not configured to connect to machine */
	}
	else if (so->machine[md].connection_status_valid != 1)
	{				
		buffer[0] = '2';  		/* connection status not available */
	}	
	else if (so->machine[md].connection_status == 1)
	{
		buffer[0] = '1';  		/* machine is connected  */
	}
	else
	{
		buffer[0] = '0';  		/* machine is not connected  */
	}

	pthread_mutex_unlock(&so->pthread_mutex);


	buffer[1] = '\0';
	*buffer_len = 1;


	return 0;
}

