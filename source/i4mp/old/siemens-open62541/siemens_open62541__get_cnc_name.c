#include "siemens_open62541__private.h"


int siemens_open62541__get_cnc_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	rc = siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if (rc != 0)
	{
		return rc;
	}


	strcpy(buffer, so->machine[md].config.cnc_name);
	*buffer_len = strlen(buffer);


	return 0;


}

