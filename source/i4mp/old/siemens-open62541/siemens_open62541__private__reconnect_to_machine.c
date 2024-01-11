#include "siemens_open62541__private.h"



int siemens_open62541__private__reconnect_to_machine (int md)
{

	int rc;
	

	if ((md > so->machine_count) || (md < 0))
	{
		return -100;
	}


	if (so->machine[md].config.online == 0)
	{
		return 0;
	}
	

	rc = so->machine[md].reconnect_to_machine(md);


	return rc;

}


