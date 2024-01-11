#include "okuma_mt__private.h"


int okuma_mt__private__allocate_machines_resources__simulated (int md)
{	


	if ((md < 0) || (md >= om->machine_count))
	{
		return -100;
	}

	om->machine[md].resources_allocated = 1;

	return 0;
}


