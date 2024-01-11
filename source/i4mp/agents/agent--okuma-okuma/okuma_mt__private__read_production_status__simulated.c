#include "okuma_mt__private.h"


int okuma_mt__private__read_production_status__simulated (int md)
{

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].production_status_valid = om->machine[md].production_status_valid_simulated;
	om->machine[md].production_status = om->machine[md].production_status_simulated;

	return 0;

}

