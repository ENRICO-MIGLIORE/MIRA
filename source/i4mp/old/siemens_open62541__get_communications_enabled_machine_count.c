#include "siemens_open62541__private.h"


int siemens_open62541__get_communications_enabled_machine_count (size_t* count)
{
	
	if (so->configured != 1)
	{
		return -100;
	}

	if (count == NULL)
	{
		return -200;
	}


	*count = so->machine_count;


	return 0;
}
