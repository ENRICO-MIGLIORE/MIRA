#include "okuma_mt__private.h"


static char *fn = "okuma_mt__private__allocate_machines_resources__real()";


int okuma_mt__private__allocate_machines_resources__real (int md)
{	

	if ((md >= om->machine_count) || (md < 0))
	{
		return -100;
	}


	om->machine[md].resources_allocated = 1;


	return 0;
}


