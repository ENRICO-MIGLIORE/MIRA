#include "siemens_open62541__private.h"


static char* fn = "siemens_open62541__private__connect_to_machine__simulated()";


int siemens_open62541__private__connect_to_machine__simulated (int md)
{

	if ((md > so->machine_count) || (md < 0))
	{
		return -100;
	}

	so->machine[md].connection_status = 1;
	
	utils__printf__info(&so->pf, fn, 0, "agent connected to \"%s(%d)\" in simulation mode", so->machine[md].config.name, so->machine[md].config.id);
	
	return 0;

}
