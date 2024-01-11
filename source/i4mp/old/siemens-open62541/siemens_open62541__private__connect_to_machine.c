#include "siemens_open62541__private.h"


static char* fn = "siemens_open62541__private__connect_to_machine()";


int siemens_open62541__private__connect_to_machine (int md)
{

	int rc;

	if ((md > so->machine_count) || (md < 0))
	{
		return -100;
	}


	if (so->machine[md].config.online == 0)
	{		
		utils__printf__info(&so->pf, fn, 0, "agent not connected to \"%s(%d)\"", so->machine[md].config.name, so->machine[md].config.id);
		return 0;
	}

	rc = so->machine[md].connect_to_machine(md);


	return rc;

}


