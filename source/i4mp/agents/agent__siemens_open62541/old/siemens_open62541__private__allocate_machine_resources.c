#include "siemens_open62541__private.h"


int siemens_open62541__private__allocate_machine_resources (int md)
{	

	int rc;


	if ((md >= so->machine_count) || (md < 0))
	{
		return -100;
	}


	rc = so->machine[md].allocate_machine_resources(md);


	return rc;
}
