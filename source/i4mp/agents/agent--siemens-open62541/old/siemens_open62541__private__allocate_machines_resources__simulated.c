#include "siemens_open62541__private.h"


int siemens_open62541__private__allocate_machines_resources__simulated (int md)
{	


	if ((md < 0) || (md >= so->machine_count))
	{
		return -100;
	}

	so->machine[md].resources_allocated = 1;

	return 0;
}


