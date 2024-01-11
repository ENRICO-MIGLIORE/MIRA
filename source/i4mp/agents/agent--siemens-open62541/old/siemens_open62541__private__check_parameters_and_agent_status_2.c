#include "siemens_open62541__private.h"



int siemens_open62541__private__check_parameters_and_agent_status_22 (int md, char* buffer, size_t buffer_size, size_t len)
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
		return -300;
	}

	if (buffer == NULL)
	{
		return -400;
	}

	if (len > buffer_size)
	{
		return -500;
	}

	return 0;

}