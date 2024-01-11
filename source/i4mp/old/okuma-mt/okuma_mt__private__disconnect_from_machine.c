#include "okuma_mt__private.h"


int okuma_mt__private__disconnect_from_machine (int md)
{
	
	int rc;

	if ((md > om->machine_count) || (md < 0))
	{
		return -100;
	}


	if (om->machine[md].config.online == 0)
	{			
		return 0;
	}

	rc = om->machine[md].disconnect_from_machine(md);

	return rc;

}


