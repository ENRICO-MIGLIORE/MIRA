#include "siemens_open62541__private.h"


int siemens_open62541__get_enable_communications_status (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t fd;
	size_t buffer_size_min;
	int rc;


	rc = siemens_open62541__check_agent_status();
	if (rc != 0)
	{
		return -100;
	}

	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_64;

	rc = siemens_open62541__check_parameters(machine_id, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return -200;
	}

	fd = machine_id - 1;


	strcpy(buffer, so->machine[fd].config.enable_communications);
	*buffer_len = strlen(buffer);


	return 0;
}

