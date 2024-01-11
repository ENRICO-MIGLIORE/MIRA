#include "okuma_mt__private.h"


static char* fn = "okuma_mt__private__connect_to_machine()";


int okuma_mt__private__connect_to_machine (int md)
{

	int rc;

	if ((md > om->machine_count) || (md < 0))
	{
		return -100;
	}


	if (om->machine[md].config.online == 0)
	{		
		utils__printf__info(&om->pf, fn, 0, "agent not connected to \"%s(%d)\"", om->machine[md].config.name, om->machine[md].config.id);
		return 0;
	}

	rc = om->machine[md].connect_to_machine(md);


	return rc;

}


