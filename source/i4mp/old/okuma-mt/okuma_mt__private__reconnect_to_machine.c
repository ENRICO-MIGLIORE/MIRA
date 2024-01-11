#include "okuma_mt__private.h"



int okuma_mt__private__reconnect_to_machine (int md)
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
	

	rc = om->machine[md].reconnect_to_machine(md);


	return rc;

}


