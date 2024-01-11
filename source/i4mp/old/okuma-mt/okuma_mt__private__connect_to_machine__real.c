#include "okuma_mt__private.h"



static char* fn = "okuma_mt__private__connect_to_machine__real()";


int okuma_mt__private__connect_to_machine__real (int md)
{

	if ((md < 0) || (md > om->machine_count))
	{
		return -100;
	}


	//om->machine[md].connection_status = 1;
	
	utils__printf__info(&om->pf, fn, 0, "agent will connect to \"%s(%d)\" in a few seconds", om->machine[md].config.name, om->machine[md].config.id);

	return 0;
}
