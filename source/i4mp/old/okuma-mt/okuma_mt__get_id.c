#include "okuma_mt__private.h"


int okuma_mt__get_id (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;
	int len;


	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;

	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if (rc != 0)
	{
		return rc;
	}


	len = sprintf(buffer, "%d", om->machine[md].config.id);

	if (len <= 0)
	{
		return -5000;
	}

	*buffer_len = (size_t) len;


	return 0;
}

