#include "siemens_open62541__private.h"


int siemens_open62541__get_online_status (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;
	

	rc = siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return rc;
	}

	if (so->machine[md].config.online == 0)
	{
		strcpy(buffer, "0");
	}
	else
	{
		strcpy(buffer, "1");
	}

	*buffer_len = 1;

	return 0;
}

