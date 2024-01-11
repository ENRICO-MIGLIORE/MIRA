#include "siemens_open62541__private.h"


int siemens_open62541__check_agent_status (void)
{

	if (so->configured != 1)
	{
		return -100;
	}

	if (so->started != 1)
	{
		return -200;
	}

	return 0;

}








