#include "siemens_open62541__private.h"


int siemens_open62541__private__check_parameters_and_agent_status (int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (so == NULL)
	{
		return -100;
	}

	if (so->configured != 1)
	{
		return -200;
	}

	if ((md >= so->machine_count) || (md < 0))
	{
		return -400;
	}

	if (buffer == NULL)
	{
		return -500;
	}

	if (buffer_size < buffer_size_min)
	{
		return -600;
	}

	if (buffer_len == NULL)
	{
		return -700;
	}

	return 0;

}








