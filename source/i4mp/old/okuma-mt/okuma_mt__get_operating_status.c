#include "okuma_mt__private.h"


int okuma_mt__get_operating_status (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;


	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return rc;
	}

	if (om->machine[md].config.operating == 0)
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

