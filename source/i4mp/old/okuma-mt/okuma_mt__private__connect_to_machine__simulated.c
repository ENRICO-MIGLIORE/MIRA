#include "okuma_mt__private.h"


static char* fn = "okuma_mt__private__connect_to_machine__simulated()";


int okuma_mt__private__connect_to_machine__simulated (int md)
{

	if ((md > om->machine_count) || (md < 0))
	{
		return -100;
	}

	om->machine[md].connection_status = 1;
	

	utils__printf__info(&om->pf, fn, 0, "agent connected to \"%s(%d)\" in simulation mode", om->machine[md].config.name, om->machine[md].config.id);
	
	return 0;

}
