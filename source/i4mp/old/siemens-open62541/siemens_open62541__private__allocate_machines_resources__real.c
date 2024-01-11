#include "siemens_open62541__private.h"


static char *fn = "siemens_open62541__private__allocate_machines_resources__real()";


int siemens_open62541__private__allocate_machines_resources__real (int md)
{	

	if ((md >= so->machine_count) || (md < 0))
	{
		return -100;
	}

	so->machine[md].client = UA_Client_new();

	if (so->machine[md].client == NULL)
	{
		utils__printf__error(&so->pf, fn, -200, "UA_Client_new() returned NULL for machine id %d", fn, so->machine[md].config.id);
		return -200;
	}

	so->machine[md].resources_allocated = 1;


	return 0;
}


