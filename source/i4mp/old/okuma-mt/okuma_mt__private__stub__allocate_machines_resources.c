#include "okuma_mt__private.h"


int okuma_mt__private__allocate_machine_resources (int md)
{	

	int rc;


	if ((md >= om->machine_count) || (md < 0))
	{
		return -100;
	}


	rc = om->machine[md].allocate_machine_resources(md);


	return rc;
}
